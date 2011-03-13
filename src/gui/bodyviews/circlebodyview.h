#ifndef CIRCLEBODYVIEW_H
#define CIRCLEBODYVIEW_H

#include "bodyview.h"
#include "circlebody.h"

class CircleBodyView : public BodyView
{
public:
	CircleBodyView(const CircleBody& body, QGraphicsItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;

};

#endif // CIRCLEBODYVIEW_H
