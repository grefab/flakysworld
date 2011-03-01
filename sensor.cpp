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
	/* we need to know how a point from our parent maps to world coordinates for
	 * performing ray casts later on.
	 */
	mapParentToWorld_ = mapParentToWorld;
	updateMapToWorld();
}

const QTransform& Sensor::mapToWorld() const
{
	/* tells how a local point maps to world coordinates. */
	return mapToWorld_;
}

void Sensor::updateMapToWorld()
{
	/* when we map our local point to the parent coordinates and these again to the wolrd,
	 * we achieve mapping local points to the world. woohoo!
	 */
	mapToWorld_ = mapToParent_ * mapParentToWorld_;

	/* when we have to recalculate our mapping relative to the world it is plausible that
	 * our world position has changed. tell everyone!
	 */
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
