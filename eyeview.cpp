#include "eyeview.h"
#include <QPainter>
#include <QVector>

EyeView::EyeView(const Eye& eye, QGraphicsItem *parent) :
		QGraphicsObject(parent),
		eye_(eye)
{
	/* create our eye-shape */
	polygon_ << QPointF(-0.01f, 0.0f) << QPointF(0.01f, -0.01f) << QPointF(0.01f, 0.01f);

	/* populate rays */
	rays_ = eye_.rays();

	/* initialize rays */
	for(int i = 0; i < rays_.size(); ++i) {
	    output_.append(0);
	}

	/* get notified of position changes */
	connect(&eye, SIGNAL(positionChanged(QTransform)), this, SLOT(eyePositionChanged(QTransform)));

	/* get notified of sesor input changes */
	connect(&eye, SIGNAL(sensed(QList<qreal>)), this, SLOT(retinaUpdated(QList<qreal>)));
}

void EyeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	/* draw a small indicator that we can see the plain eye */
	painter->drawPolygon(polygon_);

	/* make the rays a bit transparent */
	static const QColor color = QColor(0, 0, 0, 16);
	painter->setPen(QPen(color));
	painter->setBrush(QBrush(color));

	/* draw the rays */
	QPolygonF poly;

	poly << QPointF(0,0);

	QList<QLineF> drawLines = rays_;
	for( int i = 0; i < drawLines.size(); ++i) {
		QLineF& line = drawLines[i];
		qreal fraction = output_[i];

		line.setLength(line.length() * fraction);

		poly << line.p2();
	}

	painter->drawPolygon(poly);
	painter->drawLines(drawLines.toVector());
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
