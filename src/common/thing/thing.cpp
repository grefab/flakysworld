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

	update();
}

void Thing::setPosRot(const QPointF& position, qreal rotation)
{
	position_ = position;
	rotation_ = rotation;
	update();
}

void Thing::setPosition(const QPointF& position)
{
	position_ = position;
	update();
}

void Thing::setRotation(qreal rotation)
{
	rotation_ = rotation;
	update();
}

void Thing::update()
{
	updateMapToWorld();

	emit changedPosition(getWorldMap());
	emit updated(position_, rotation_);
}

void Thing::updateMapToWorld()
{
	mapToWorld_.reset();
	mapToWorld_.translate(position().x(), position().y());
	mapToWorld_.rotateRadians(rotation());
}
