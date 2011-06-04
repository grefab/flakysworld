#include "thing.h"
#include <QUuid>

Thing::Model::Model(QPolygonF shape, QPointF position, qreal rotation, QString id) :
	id_(id),
	shape_(shape),
	position_(position),
	rotation_(rotation)
{
	/* create an id if we have none given */
	if ( id_ == "" ) {
		id_ = QUuid::createUuid().toString();
	}
}

Thing::Thing(QPolygonF shape, QPointF position, qreal rotation, QString id, QObject *parent) :
	QObject(parent),
	model_(shape, position, rotation, id)
{
	update();
}

void Thing::setPosRot(const QPointF& position, qreal rotation)
{
	model_.position_ = position;
	model_.rotation_ = rotation;
	update();
}

void Thing::setPosition(const QPointF& position)
{
	model_.position_ = position;
	update();
}

void Thing::setRotation(qreal rotation)
{
	model_.rotation_ = rotation;
	update();
}

void Thing::update()
{
	updateMapToWorld();

	emit changedPosition(getWorldMap());
	emit updated(model_.position_, model_.rotation_);
}

void Thing::updateMapToWorld()
{
	mapToWorld_.reset();
	mapToWorld_.translate(position().x(), position().y());
	mapToWorld_.rotateRadians(rotation());
}
