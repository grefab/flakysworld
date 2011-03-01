#include "sensor.h"
#include "world.h"
#include <QUuid>

Sensor::Sensor(const World& world, const QPointF position, qreal rotation, QString id, QObject *parent) :
	QObject(parent),
	world_(world),
	position_(position),
	rotation_(rotation)
{
	id_ = id == "" ? QUuid::createUuid().toString() : id;

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

const QTransform& Sensor::mapToWorld() const
{
	return mapToWorld_;
}

void Sensor::updateMapToWorld()
{
	mapToWorld_ = mapToParent_ * mapParentToWorld_;

	emit positionChanged(mapToWorld_);
}

void Sensor::updateIfNeeded(const QList<qreal>& newOutput) const
{
	/* only singal a change if there was actually one. */
	if ( isUpdateNeeded(newOutput) ) {
		emit sensed(newOutput);
	}
}

bool Sensor::isUpdateNeeded(const QList<qreal>& newOutput) const
{
	/* check for changes between last and current output. */
	if ( newOutput != lastOutput_ ) {
		/* kinda dirty hack to modify our last output without admitting that we violate constness. */
		QList<qreal>& nonconst_lastOutput = const_cast< QList<qreal>& >(lastOutput_);
		nonconst_lastOutput = newOutput;

		return true;
	}

	return false;
}
