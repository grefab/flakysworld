#include "thing.h"
#include <QUuid>

Thing::Thing(QPolygonF shape, QPointF position, qreal rotation, QObject *parent) :
	QObject(parent),
	shape_(shape),
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

	emit changedPosition(getWorldMap());
}

void Thing::updateMapToWorld()
{
	mapToWorld_.reset();
	mapToWorld_.translate(position().x(), position().y());
	mapToWorld_.rotateRadians(rotation());
}
