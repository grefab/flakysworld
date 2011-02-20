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

	Flaky* flaky() { return &flaky_; }

public slots:
	void keyPressHandler(Qt::Key key);
	void keyReleaseHandler(Qt::Key key);

protected:
	void setup();

	/* flaky has always been and needs no construction. */
	Flaky flaky_;

	World* world_;
	Engine* engine_;
};

#endif // UNIVERSE_H
