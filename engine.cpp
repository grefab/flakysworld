#include "engine.h"
#include <QTimerEvent>
#include "bodycontroller.h"

const float FPS = 25;

Engine::Engine(QObject *parent) :
		QThread(parent),
		simulationTimerId_(0),
		stepsPerformed_(0)
{
	world_ = new b2World(/* gravity = */ b2Vec2(0.0f, 0.0f), /* doSleep = */ true);

	/* priority has to be higher than the gui thread, so diplay is smooth. otherwise there is flicker. */
	QThread::start(QThread::HighestPriority);

	stepsPerSecondTimerId_ = startTimer(1000);
}

Engine::~Engine()
{
	QThread::terminate();
	delete world_;
}

void Engine::start()
{
	simulationTimerId_ = startTimer(1000 / FPS);
}

void Engine::stop()
{
	if ( simulationTimerId_ ) {
		killTimer(simulationTimerId_);
	}
}

Body* Engine::addBody(Body* body)
{
	/* it's ours now! */
	body->moveToThread(this);
	body->setWorld(world_);
	bodies_.insert(body->id(), body);

	/* update body if necessary */
	connect(this, SIGNAL(simulationStepHappened()), body, SLOT(simulationStep()));

	/* allows for chaining */
	return body;
}

b2World* Engine::world()
{
	return world_;
}

void Engine::timerEvent(QTimerEvent *event)
{
	if ( event->timerId() == simulationTimerId_ ) {
		performSimulationStep();
	} else if ( event->timerId() == stepsPerSecondTimerId_ ) {
		qDebug() << stepsPerformed_;
		stepsPerformed_ = 0;


		BodyController(bodies_["flaky"]).push(QPointF(0.01, 0), QPointF(-0.03, 0.03));
		BodyController(bodies_["flaky"]).push(QPointF(0.01, 0), QPointF(-0.03, -0.03));
	}
}

void Engine::performSimulationStep()
{
	const int32 B2_VELOCITYITERATIONS = 10;
	const int32 B2_POSITIONITERATIONS = 10;
	const float32 B2_TIMESTEP = 1.0f / FPS;

	world_->Step(B2_TIMESTEP, B2_VELOCITYITERATIONS, B2_POSITIONITERATIONS);
	world_->ClearForces();

	emit simulationStepHappened();

	++stepsPerformed_;
}
