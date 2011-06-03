#include "thruster.h"

Thruster::Thruster(const Being& being, const QPointF position, qreal rotation, QString id, QObject *parent) :
	Actuator(being, position, rotation, id, parent)
{
}

void Thruster::receiveInput(QList<qreal> input)
{
	/* convert our one neuron to force */
	QPointF force = QPointF(input[0], 0);

	/* push body */
	being_.body()->applyForce(force, position_);
}

