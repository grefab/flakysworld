#include "sensor.h"
#include "world.h"
#include <QUuid>

Sensor::Sensor(const World& world, QObject *parent) :
	QObject(parent),
	world_(world)
{
	id_ = QUuid::createUuid().toString();
}

QString Sensor::id() const
{
	return id_;
}
