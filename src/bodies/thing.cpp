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

const QString KEY_THING_ID = "id";
const QString KEY_THING_SHAPE = "shape";
const QString KEY_THING_POSITION = "position";
const QString KEY_THING_ROTATION = "rotation";

QVariantMap Thing::getSerialized()
{
	/* we need to serailize everything, i.e. id, shape, position and rotation. */
	QVariantMap resultMap;

	resultMap.insert(KEY_THING_ID, id_);
	resultMap.insert(KEY_THING_SHAPE, qpolygonf2qvariant(shape_));
	resultMap.insert(KEY_THING_POSITION, qpointf2qvariant(position_));
	resultMap.insert(KEY_THING_ROTATION, rotation_);

	return resultMap;
}

void Thing::fromVariant(QVariantMap serialized)
{
	QString id = serialized[KEY_THING_ID].toString();
	QPolygonF shape = qvariant2qpolygonf(serialized[KEY_THING_SHAPE]);
	QPointF position = qvariant2qpointf(serialized[KEY_THING_POSITION]);
	qreal rotation = serialized[KEY_THING_ROTATION].toReal();
}
