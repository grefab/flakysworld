#include "world.h"
#include <QThread>
#include "engine.h"

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

	/* update body if necessary */
	connect(this, SIGNAL(simulationStepHappened()), body, SLOT(simulationStep()));

	/* allows for chaining */
	return body;
}

b2World* World::world()
{
	return world_;
}

QList<Body*> World::bodies() const
{
	return bodies_.values();
}

void World::performSimulationStep(float32 timestep)
{
	const int32 B2_VELOCITYITERATIONS = 10;
	const int32 B2_POSITIONITERATIONS = 10;
	//	const float32 B2_TIMESTEP = 1.0f / FPS;

	world_->Step(timestep, B2_VELOCITYITERATIONS, B2_POSITIONITERATIONS);
	world_->ClearForces();

	emit simulationStepHappened();

	if ( QThread::currentThread() != engine_ ) {
		qDebug() << "world not running in engine!";
	}
}

World::RayHit World::rayCast(const QPointF& from, const QPointF& to) const
{
	class RayCastCallback : public b2RayCastCallback
	{
	public:
		RayCastCallback() : fixture_(NULL) {}

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
			fixture_ = fixture;
			point_ = point;
			normal_ = normal;
			fraction_ = fraction;

			/* using this we find the closest intersection point to our ray origin. */
			return fraction;
		}

		b2Fixture* fixture_;
		b2Vec2 point_;
		b2Vec2 normal_;
		float32 fraction_;
	} callback;

	world_->RayCast(&callback, b2Vec2(from.x(), from.y()), b2Vec2(to.x(), to.y()));

	return RayHit(
			/* find body for fixture found */
			bodies_.value( static_cast<Body*>(callback.fixture_->GetBody()->GetUserData())->id() ),

			/* convert b2 parameters into our struct */
			QPointF(callback.point_.x, callback.point_.y),
			callback.fraction_
			);
}
