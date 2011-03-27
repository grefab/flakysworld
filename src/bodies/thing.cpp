#include "thing.h"
#include <QUuid>
#include "interface/persistence.h"

Thing::Thing(QPolygonF shape, QPointF position, qreal rotation, QString id, QObject *parent) :
	QObject(parent),
	id_(id),
	shape_(shape),
	position_(position),
	rotation_(rotation)
{
	/* create an id if we have none given */
	if ( id_ == "" ) {
		id_ = QUuid::createUuid().toString();
	}

	updateMapToWorld();
}

void Thing::update(QPointF position, qreal rotation)
{
	position_ = position;
	rotation_ = rotation;
	updateMapToWorld();

	emit changedPosition(getWorldMap());
}

void Thing::updateMapToWorld()
{
	mapToWorld_.reset();
	mapToWorld_.translate(position().x(), position().y());
	mapToWorld_.rotateRadians(rotation());
}

QVariantMap Thing::getSerialized()
{
	/* we need to serailize everything, i.e. id, shape, position and rotation. */
	QVariantMap resultMap;

	resultMap.insert("id", id_);
	resultMap.insert("shape", qpolygonf2qvariant(shape_));
	resultMap.insert("position", qpointf2qvariant(position_));
	resultMap.insert("rotation", rotation_);

	return resultMap;
}
