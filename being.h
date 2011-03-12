#ifndef BEING_H
#define BEING_H

#include <QObject>
#include "body.h"
#include <QList>
#include <QHash>
#include "sensor.h"

class World;

class Being : public QObject
{
	Q_OBJECT
public:
	explicit Being(World* world, QObject *parent = 0);
	~Being();

	Body* body() const { return body_; };
	QList<Sensor*> sensors() const { return sensors_.values(); };

protected:
	void addSensor(Sensor* sensor);

	const World& world_;
	Body* body_;
	QHash<QString, Sensor*> sensors_;

};

#endif // BEING_H
