#ifndef POLYGONBODYVIEW_H
#define POLYGONBODYVIEW_H

#include "bodyview.h"
#include "polygonbody.h"

class PolygonBodyView : public BodyView
{
public:
	PolygonBodyView(const PolygonBody& body, QGraphicsItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;

};

#endif // POLYGONBODYVIEW_H
