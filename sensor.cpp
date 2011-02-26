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

	mapToParent_.translate(position_.x(), position_.y());
	mapToParent_.rotateRadians(rotation_);

	updateMapToWorld();
}

QString Sensor::id() const
{
	return id_;
}

void Sensor::setMapParentToWorld(QTransform mapParentToWorld)
{
	mapParentToWorld_ = mapParentToWorld;
	updateMapToWorld();
}

QTransform Sensor::mapToWorld() const
{
	return mapToWorld_;
}

void Sensor::updateMapToWorld()
{
	mapToWorld_ = mapToParent_ * mapParentToWorld_;

	emit positionChanged(mapToWorld_);
}
