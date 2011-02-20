#include "engine.h"
#include <QTimer>
#include <QTimerEvent>
#include "bodycontroller.h"
#include <QDebug>

const float FPS = 25;

Engine::Engine(World* world, QObject *parent) :
		QThread(parent),
		world_(world),
		stepsPerformed_(0)
{
	moveToThread(this);
	world->moveToThread(this);
	world_->setEngine(this);
}

Engine::~Engine()
{
	QThread::terminate();
}

void Engine::start()
{
	QThread::start(IdlePriority);
}

void Engine::run()
{
	QTimer simulationTimer;
	connect(&simulationTimer, SIGNAL(timeout()), this, SLOT(simulationStep()));
	simulationTimer.start(1000 / FPS);

	QTimer fpsTimer;
	connect(&fpsTimer, SIGNAL(timeout()), this, SLOT(printFPS()));
	fpsTimer.start(1000);

	exec();
}


void Engine::simulationStep()
{
	world_->performSimulationStep(1.0f / FPS);
	++stepsPerformed_;
}

void Engine::printFPS()
{
	qDebug() << stepsPerformed_;
	stepsPerformed_ = 0;

	BodyController(world_->bodies_["flaky"]).push(QPointF(0.01, 0), QPointF(-0.03, 0.03));
	BodyController(world_->bodies_["flaky"]).push(QPointF(0.01, 0), QPointF(-0.03, -0.03));
}
