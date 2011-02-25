#include "eye.h"
#include <QTransform>


Eye::Eye(World* world, qreal lengthOfSight, QObject *parent) :
	QObject(parent),
	world_(world),
	lengthOfSight_(lengthOfSight)
{
}

void Eye::performSensing(QPointF position, qreal rotation)
{
	QTransform trans;
	trans.translate(position.x(), position.y());

	QTransform rot;
	rot.rotate(rotation);

	QPointF origin = QPointF(0, 0);
	QPointF destination = QPointF(1.0f, 0.0f);

	QLineF ray = QLineF(origin, destination);

	QLineF transformedRay = trans.map(rot.map(ray));
}
