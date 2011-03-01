#include "sensor.h"
#include "world.h"

Sensor::Sensor(const World& world, const QPointF position, qreal rotation, QString id, QObject *parent) :
	Organ(world, position, rotation, id, parent)
{
}

void Sensor::updateIfNeeded(const QList<qreal>& newOutput) const
{
	/* only singal a change if there was actually one. */
	if ( isUpdateNeeded(newOutput) ) {
		emit sensed(newOutput);
	}
}

bool Sensor::isUpdateNeeded(const QList<qreal>& newOutput) const
{
	/* check for changes between last and current output. */
	if ( newOutput != lastOutput_ ) {
		/* kinda dirty hack to modify our last output without admitting that we violate constness. */
		QList<qreal>& nonconst_lastOutput = const_cast< QList<qreal>& >(lastOutput_);
		nonconst_lastOutput = newOutput;

		return true;
	}

	return false;
}
