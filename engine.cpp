#include "engine.h"
#include <QTimer>
#include <QTimerEvent>
#include "bodycontroller.h"

const float FPS = 50;

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
	QThread::start(HighestPriority);
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
	emit updatedFPS(stepsPerformed_);
	stepsPerformed_ = 0;
}
