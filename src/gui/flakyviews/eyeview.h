#ifndef EYEVIEW_H
#define EYEVIEW_H

#include <QGraphicsObject>
#include "eye.h"
#include <QList>
#include <QLineF>

class EyeView : public QGraphicsObject
{
	Q_OBJECT

public:
	explicit EyeView(const Eye& eye, QGraphicsItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;

protected:
	const Eye& eye_;

private slots:
	void eyePositionChanged(QTransform transform);
	void retinaUpdated(QList<qreal> output);

private:
	QPolygonF polygon_;
	QList<QLineF> rays_;
	QRectF boundingRect_;
	QList<qreal> output_;
};

#endif // EYEVIEW_H
