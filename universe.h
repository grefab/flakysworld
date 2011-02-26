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
	explicit Universe(QObject *parent = 0);
	~Universe();

	Flaky* flaky() { return flaky_; }
	World* world() { return world_; }
	Engine* engine() { return engine_; }

public slots:
	void keyPressHandler(Qt::Key key);
	void keyReleaseHandler(Qt::Key key);

protected:
	void setup();

	Flaky* flaky_;
	World* world_;
	Engine* engine_;
};

#endif // UNIVERSE_H
