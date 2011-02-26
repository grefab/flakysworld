#include "bodyview.h"

BodyView::BodyView(const Body& body, QGraphicsItem *parent) :
		QAbstractGraphicsShapeItem(parent),
		body_(body)
{
	/* we need the body only to connect to it. no reference is stored. */
	connect(&body, SIGNAL(changedPosition(QPointF,qreal)), this, SLOT(bodyChanged(QPointF,qreal)));

	/* initially set our location parameters */
	bodyChanged(body.position(), body.rotation());
}

void BodyView::bodyChanged(QPointF position, qreal rotation)
{
	setPos(QPointF(position.x(), -position.y()));
	setRotation(-rotation * 360.0 / (2 * PI));
}
