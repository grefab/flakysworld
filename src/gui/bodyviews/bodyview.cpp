#include "bodyview.h"
#include <QBrush>

BodyView::BodyView(const Body& body, QGraphicsItem *parent) :
		QGraphicsPolygonItem(parent),
		body_(body)
{
	/* colorize! */
	setBrush(QColor(128 + qrand() % 128, 128 + qrand() % 128, 128 + qrand() % 128));

	/* we need the body only to connect to it. no reference is stored. */
	connect(&body, SIGNAL(changedPosition(QTransform)), this, SLOT(bodyChanged(QTransform)));

	/* initially set our location parameters */
	bodyChanged(body.getWorldMap());

	/* adept our model's shape */
	setPolygon(body.shape());
}

void BodyView::bodyChanged(QTransform transformation)
{
	/* mirroring on the x axis to take care for Qt's screen coordinates. */
	static const QTransform mirror(1, 0, 0, 0, -1, 0, 0, 0, 1);

	setTransform(transformation * mirror);
}
