#include "thing.h"
#include <QUuid>

Thing::Thing(QPointF position, qreal rotation, QObject *parent) :
	QObject(parent),
	position_(position),
	rotation_(rotation)
{
	id_ = QUuid::createUuid().toString();
	updateMapToWorld();
}

void Thing::update(QPointF position, qreal rotation)
{
	position_ = position;
	rotation_ = rotation;
	updateMapToWorld();
}

void Thing::updateMapToWorld()
{
	mapToWorld_.reset();
	mapToWorld_.translate(position().x(), position().y());
	mapToWorld_.rotateRadians(rotation());
}
