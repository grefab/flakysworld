#include "sensor.h"
#include "world.h"
#include <QUuid>

Sensor::Sensor(const World& world, const QPointF position, qreal rotation, QObject *parent) :
	QObject(parent),
	world_(world),
	position_(position),
	rotation_(rotation)
{
	id_ = QUuid::createUuid().toString();
}

QString Sensor::id() const
{
	return id_;
}
