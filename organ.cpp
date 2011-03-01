#include "organ.h"
#include <QUuid>

Organ::Organ(const World& world, const QPointF position, qreal rotation, QString id, QObject *parent) :
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

QString Organ::id() const
{
	return id_;
}

void Organ::setMapParentToWorld(QTransform mapParentToWorld)
{
	/* we need to know how a point from our parent maps to world coordinates for
	 * performing ray casts later on.
	 */
	mapParentToWorld_ = mapParentToWorld;
	updateMapToWorld();
}

const QTransform& Organ::mapToWorld() const
{
	/* tells how a local point maps to world coordinates. */
	return mapToWorld_;
}

void Organ::updateMapToWorld()
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

