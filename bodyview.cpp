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
	setTransform(transformation);

//	setPos(QPointF(position.x(), -position.y()));
//	setRotation(-rotation * 360.0 / (2 * PI));
}
