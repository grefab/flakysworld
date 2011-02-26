#include "bodyview.h"

BodyView::BodyView(const Body& body, QGraphicsItem *parent) :
		QAbstractGraphicsShapeItem(parent),
		body_(body)
{
	/* we need the body only to connect to it. no reference is stored. */
	connect(&body, SIGNAL(changedPosition(QTransform)), this, SLOT(bodyChanged(QTransform)));

	/* initially set our location parameters */
	bodyChanged(body.getWorldMap());
}

void BodyView::bodyChanged(QTransform transformation)
{
	/* mirroring on the x axis to take care for Qt's screen coordinates. */
	static const QTransform mirror(1, 0, 0, 0, -1, 0, 0, 0, 1);

	setTransform(transformation * mirror);
}
