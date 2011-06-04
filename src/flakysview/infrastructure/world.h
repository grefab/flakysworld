#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QMap>
#include "thing/thing.h"

class World : public QObject
{
	Q_OBJECT
public:
	explicit World(QObject *parent = 0);

	/* if a new thing has been added, this thing is returned. otherwise, NULL is returned. */
	Thing* updateThing(const Thing::Model& thingModel);

private:
	QMap<QString, Thing*> things_;
};

#endif // WORLD_H
