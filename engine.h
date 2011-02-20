#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>
#include "world.h"

class Engine : public QThread
{
	Q_OBJECT

public:
	Engine(World* world, QObject *parent = 0);
	~Engine();

	void start();

signals:
	void updateFPS(int fps);

protected slots:
	void simulationStep();
	void printFPS();

protected:
	void run();

	World* world_;

private:
	unsigned long stepsPerformed_;
};

#endif // ENGINE_H
