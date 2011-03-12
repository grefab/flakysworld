#ifndef BEING_H
#define BEING_H

#include <QObject>
#include "body.h"
#include <QList>
#include <QHash>

class World;
class Sensor;

class Being : public QObject
{
	Q_OBJECT

protected:
	/* we do not allow plain beings, but just inherited ones. */
	explicit Being(World* world, Body* body, QObject *parent = 0);

public:
	~Being();

	const World& world() const { return world_; }
	Body* body() const { return body_; }
	QList<Sensor*> sensors() const { return sensors_.values(); }

protected:
	void addSensor(Sensor* sensor);

private:
	const World& world_;
	Body* body_;
	QHash<QString, Sensor*> sensors_;

};

#endif // BEING_H
