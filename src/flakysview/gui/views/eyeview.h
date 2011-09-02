#ifndef EYEVIEW_H
#define EYEVIEW_H

#include <QGraphicsObject>
#include "thing/thing.h"
#include <QList>
#include <QLineF>

class EyeView : public QGraphicsObject
{
	Q_OBJECT

public:
	explicit EyeView(QGraphicsItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;

protected slots:
	void retinaUpdated(QList<qreal> output);

private:
	void initRays();

	QPolygonF eyeSymbol_;
	QList<QLineF> rays_;
	QRectF boundingRect_;
	QList<qreal> output_;

};

#endif // EYEVIEW_H
