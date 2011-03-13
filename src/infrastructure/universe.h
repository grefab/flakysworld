#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <QObject>

#include "world.h"
#include "engine.h"
#include <QList>
#include <QMap>
#include "being/being.h"

class Universe : public QObject
{
	Q_OBJECT
public:
	explicit Universe(QObject *parent = 0);
	~Universe();

	QList<Being*> beings() const { return beings_.values(); }
	const Being* being(QString id) const { return beings_.value(id); }
	World* world() { return world_; }
	Engine* engine() { return engine_; }

public slots:
	void keyPressHandler(Qt::Key key);
	void keyReleaseHandler(Qt::Key key);

protected:
	void setup();
	void addBeing(Being* being);

	QMap<QString, Being*> beings_;
	World* world_;
	Engine* engine_;
};

#endif // UNIVERSE_H
