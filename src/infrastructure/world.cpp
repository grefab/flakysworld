#include "world.h"
#include <QThread>
#include "engine.h"

#include <QMutexLocker>
#include <QDebug>

World::World(QObject *parent) :
		QObject(parent)
{
	world_ = new b2World(/* gravity = */ b2Vec2(0.0f, 0.0f), /* doSleep = */ true);
}

World::~World()
{
	delete world_;
}

Body* World::addBody(Body* body)
{
	/* it's ours now! */
	body->moveToThread(engine_);
	body->setParent(this);
	bodies_.insert(body->id(), body);

	/* we want to be notified if a thing moved */
	connect(body, SIGNAL(updated(QPointF,qreal)), this, SLOT(thingUpdated(QPointF,qreal)));

	/* allows for chaining */
	return body;
}

void World::thingUpdated(QPointF position, qreal rotation)
{
	QString thingId = static_cast<Thing*>(sender())->id();

	emit thingUpdate(thingId, position, rotation);
}

b2World* World::world() const
{
	return world_;
}

QList<Body*> World::bodies() const
{
	return bodies_.values();
}

void World::performSimulationStep(float32 timestep)
{
	QMutexLocker locker(const_cast<QMutex*>(&mutex_));

	const int32 B2_VELOCITYITERATIONS = 10;
	const int32 B2_POSITIONITERATIONS = 10;
	//	const float32 B2_TIMESTEP = 1.0f / FPS;

	/* move the world */
	world_->Step(timestep, B2_VELOCITYITERATIONS, B2_POSITIONITERATIONS);
	world_->ClearForces();

	/* tell this the bodies */
	foreach( Body* body, bodies_ ) {
		body->simulationStepHappened();
	}

	/* if any body is awake, something has changed. */
	emit worldChanged();

	if ( QThread::currentThread() != engine_ ) {
		qDebug() << "world not running in engine!";
	}
}

World::RayHit World::rayCast(const QLineF& ray) const
{
	QMutexLocker locker(const_cast<QMutex*>(&mutex_));

	return internal_rayCast(ray);
}

QList<World::RayHit> World::rayCast(const QList<QLineF>& rays) const
{
	QMutexLocker locker(const_cast<QMutex*>(&mutex_));

	QList<RayHit> results;

	foreach(const QLineF& ray, rays) {
		results.append(internal_rayCast(ray));
	}

	return results;
}

World::RayHit World::internal_rayCast(const QLineF& ray) const
{
	const QPointF& from = ray.p1();
	const QPointF& to = ray.p2();

	class RayCastCallback : public b2RayCastCallback
	{
	public:
		RayCastCallback() : fixture_(NULL), fraction_(INT_MAX /* bigger than 1 */)  {}

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
			if ( fraction < fraction_ ) {
				fixture_ = fixture;
				point_ = point;
				normal_ = normal;
				fraction_ = fraction;
			}

			/* using this we find the closest intersection point to our ray origin. */
			return fraction;
		}

		b2Fixture* fixture_;
		b2Vec2 point_;
		b2Vec2 normal_;
		float32 fraction_;

	} callback;

	world_->RayCast(&callback, b2Vec2(from.x(), from.y()), b2Vec2(to.x(), to.y()));

	if ( callback.fraction_ < 1.0f ) {
		/* we have hit something */
		void* b2bodyUserData = callback.fixture_->GetBody()->GetUserData();
		Body* hitBody = static_cast<Body*>(b2bodyUserData);

		return RayHit(
				/* find body for fixture found */
				hitBody,

				/* convert b2 parameters into our struct */
				QPointF(callback.point_.x, callback.point_.y),
				callback.fraction_
				);

	}

	/* no hit */
	return RayHit(NULL, QPointF(0, 0), 1.0f);
}
