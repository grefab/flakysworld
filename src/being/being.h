#ifndef BEING_H
#define BEING_H

#include <QObject>
#include "body.h"
#include <QList>
#include <QHash>

class World;
class Sensor;
class Actuator;

class Being : public QObject
{
	Q_OBJECT

protected:
	/* we do not allow plain beings, but just inherited ones. */
	explicit Being(World* world, Body* body, QString id = "", QObject *parent = 0);

public:
	~Being();

	QString id() const { return id_; }
	const World& world() const { return *world_; }
	Body* body() const { return body_; }
	QList<Sensor*> sensors() const { return sensors_.values(); }

protected:
	void addSensor(Sensor* sensor);
	void addActuator(Actuator* actuator);

private:
	QString id_;

	World* world_;
	Body* body_;
	QHash<QString, Sensor*> sensors_;
	QHash<QString, Actuator*> actuators_;

};

#endif // BEING_H
