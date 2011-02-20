#include "bodyview.h"

BodyView::BodyView(const Body& body, QGraphicsItem *parent) :
		QAbstractGraphicsShapeItem(parent),
		body_(body),
		lastPosition_(QPointF(0, 0)),
		lastRotation_(0)

{
	/* we need the body only to connect to it. no reference is stored. */
	connect(&body, SIGNAL(changedPosition(QPointF,qreal)), this, SLOT(bodyChanged(QPointF,qreal)));

	/* initially set our location parameters */
	bodyChanged(body.position(), body.rotation());
}

void BodyView::bodyChanged(QPointF position, qreal rotation)
{
	/* only update when we need */
	if ( lastPosition_ != position ) {
		setPos(QPointF(position.x(), -position.y()));
		lastPosition_ = position;
	}

	if ( lastRotation_ != rotation ) {
		setRotation(-rotation * 360.0 / (2 * PI));
		lastRotation_ = rotation;
	}
}
