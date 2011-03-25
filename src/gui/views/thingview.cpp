#include "thingview.h"
#include <QBrush>

ThingView::ThingView(const Thing& thing, QGraphicsItem *parent) :
		QGraphicsPolygonItem(parent),
		thing_(thing)
{
	/* colorize! */
	setBrush(QColor(128 + qrand() % 128, 128 + qrand() % 128, 128 + qrand() % 128));

	/* we need the body only to connect to it. no reference is stored. */
	connect(&thing, SIGNAL(changedPosition(QTransform)), this, SLOT(bodyChanged(QTransform)));

	/* initially set our location parameters */
	bodyChanged(thing.getWorldMap());

	/* adept our model's shape */
	setPolygon(thing.shape());
}

void ThingView::bodyChanged(QTransform transformation)
{
	/* mirroring on the x axis to take care for Qt's screen coordinates. */
	static const QTransform mirror(1, 0, 0, 0, -1, 0, 0, 0, 1);

	setTransform(transformation * mirror);
}
