#include "eyeview.h"
#include <QPainter>
#include <QVector>

EyeView::EyeView(QGraphicsItem *parent) :
		QGraphicsObject(parent)
{
	/* set our position */
	setPos(QPointF(0.3f, 0.0f));

	/* create our eye-shape */
	eyeSymbol_ << QPointF(-0.1f, 0.0f) << QPointF(0.1f, -0.1f) << QPointF(0.1f, 0.1f);

	/* populate rays */
	initRays();

	/* initialize rays */
	for(int i = 0; i < rays_.size(); ++i) {
		output_.append(0);
	}
}

void EyeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	/* draw a small indicator that we can see the plain eye */
	painter->drawPolygon(eyeSymbol_);

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

	/* draw the polygon that is spanned by the lines */
	painter->drawPolygon(poly);
	painter->drawLines(drawLines.toVector());
}

QRectF EyeView::boundingRect() const
{
	return eyeSymbol_.boundingRect();
}

void EyeView::retinaUpdated(QList<qreal> output)
{
	output_ = output;
}

void EyeView::initRays()
{
	/* empty rays */
	rays_ = QList<QLineF>();

	/* constants for display */
	const qreal visionDegrees = 90;
	const int rayCount = 32;
	const qreal length = 6.0f;

	const QPointF origin = QPointF(0, 0);
	const QPointF destination = QPointF(length, 0.0f);

	/* create rayCount rays that form a visionDegrees° angle in total */
	for( int i = 0; i < rayCount; ++i ) {
		const qreal rotation = -visionDegrees / 2.0f + ((qreal)i * (visionDegrees / (qreal)(rayCount -1)));

		QTransform rot;
		rot.rotate(rotation);

		rays_.append(QLineF(origin, rot.map(destination)));

	}
}
