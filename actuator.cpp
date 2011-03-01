#include "actuator.h"

Actuator::Actuator(const World& world, const QPointF position, qreal rotation, QString id, QObject *parent) :
	Organ(world, position, rotation, id, parent)
{
}
