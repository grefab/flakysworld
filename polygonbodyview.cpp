#include "polygonbodyview.h"
#include <QPainter>

PolygonBodyView::PolygonBodyView(const PolygonBody& body, QGraphicsItem *parent) :
		BodyView(body, parent)
{
	setBrush(QColor(128 + qrand() % 128, 128 + qrand() % 128, 128 + qrand() % 128));
}

void PolygonBodyView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter->setBrush(brush());

	const PolygonBody& polygonBody = static_cast<const PolygonBody&>(body_);
	QPolygonF drawPolygon = polygonBody.polygon();

	for ( int i = 0; i < drawPolygon.size(); ++i ) {
		drawPolygon[i].setY(-drawPolygon[i].y());
	}

	painter->drawPolygon(drawPolygon);
}

QRectF PolygonBodyView::boundingRect() const
{
	const PolygonBody& polygonBody = static_cast<const PolygonBody&>(body_);
	return polygonBody.polygon().boundingRect();
}
