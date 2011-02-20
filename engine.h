#ifndef ENGINE_H
#define ENGINE_H

#include <Box2D.h>
#include <QHash>
#include <QThread>

#include "body.h"

class Engine : protected QThread
{
	Q_OBJECT

public:
	Engine(QObject *parent = 0);
	~Engine();

	void start();
	void stop();

	/* we take ownership of the body! */
	Body* addBody(Body* body);

	b2World* world();

signals:
	void simulationStepHappened();

protected slots:
	void timerEvent(QTimerEvent *event);

private:
	void performSimulationStep();

	QHash<QString, Body*> bodies_;
	b2World *world_;

	int simulationTimerId_;
	int stepsPerSecondTimerId_;
	unsigned long stepsPerformed_;
};

#endif // ENGINE_H
