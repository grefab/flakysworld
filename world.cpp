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
	body->setWorld(world_);
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
