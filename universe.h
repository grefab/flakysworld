#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <QObject>

#include "world.h"
#include "engine.h"
#include "flaky.h"

class Universe : public QObject
{
	Q_OBJECT
public:
	explicit Universe(World* world, Engine* engine, QObject *parent = 0);

protected:
	void setup();

	Flaky flaky_;

	World* world_;
	Engine* engine_;
};

#endif // UNIVERSE_H
