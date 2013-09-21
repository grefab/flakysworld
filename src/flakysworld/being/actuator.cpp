#include "actuator.h"

Actuator::Actuator(const Being& being, const QPointF position, qreal rotation, QString id, QObject *parent) :
    Organ(being, position, rotation, id, parent)
{
}
