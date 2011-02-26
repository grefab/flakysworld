#include "eyeview.h"
#include <QPainter>

EyeView::EyeView(const Eye& eye, QGraphicsItem *parent) :
		QGraphicsObject(parent),
		eye_(eye)
{
	/* create our eye-shape */
	polygon_ << QPointF(-0.01f, 0.0f) << QPointF(0.01f, -0.01f) << QPointF(0.01f, 0.01f);

	/* populate rays */
	rays_ = eye_.rays();

	/* get notified of position changes */
	connect(&eye, SIGNAL(positionChanged(QTransform)), this, SLOT(eyePositionChanged(QTransform)));

	/* get notified of sesor input changes */
	connect(&eye, SIGNAL(hasSeen(QList<qreal>)), this, SLOT(retinaUpdated(QList<qreal>)));
}

void EyeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	/* draw a small indicator that we can see the plain eye */
	painter->drawPolygon(polygon_);

	/* draw the rays */
	QList<QLineF> drawLines = rays_;
	for( int i = 0; i < drawLines.size(); ++i) {
		QLineF line = drawLines[i];
		qreal fraction = output_[i];

		line.setLength(line.length() * fraction);

		painter->drawLine(line);
	}
}

QRectF EyeView::boundingRect() const
{
	return polygon_.boundingRect();
}

void EyeView::eyePositionChanged(QTransform transform)
{
	/* mirroring on the x axis to take care for Qt's screen coordinates. */
	static const QTransform mirror(1, 0, 0, 0, -1, 0, 0, 0, 1);

	setTransform(transform * mirror);
}

void EyeView::retinaUpdated(QList<qreal> output)
{
	output_ = output;
}
