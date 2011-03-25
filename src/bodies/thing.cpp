#include "thing.h"
#include <QUuid>

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
