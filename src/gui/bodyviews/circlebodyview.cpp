#include "circlebodyview.h"
#include <QPainter>

CircleBodyView::CircleBodyView(const CircleBody& body, QGraphicsItem *parent) :
		BodyView(body, parent)
{
	setBrush(QColor(128 + qrand() % 128, 128 + qrand() % 128, 128 + qrand() % 128));
}

void CircleBodyView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter->setBrush(brush());

	const CircleBody& circleBody = static_cast<const CircleBody&>(body_);

	/* draw circle */
	painter->drawEllipse(QPointF(0, 0), circleBody.radius(), circleBody.radius());

	/* draw rotation indicator */
	painter->drawLine(QPointF(0, 0), QPointF(circleBody.radius(), 0));
}

QRectF CircleBodyView::boundingRect() const
{
	const CircleBody& circleBody = static_cast<const CircleBody&>(body_);
	return QRectF(-circleBody.radius(), -circleBody.radius(), 2.0f * circleBody.radius(), 2.0f * circleBody.radius());
}
