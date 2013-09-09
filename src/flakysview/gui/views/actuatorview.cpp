#include "actuatorview.h"
#include <QBrush>
#include <QPen>

ActuatorView::ActuatorView(QPointF position, QGraphicsItem *parent) :
	QGraphicsPolygonItem(parent)
{
	/* locate */
	setPos(position);

	/* colorize! */
	QColor color = Qt::red;
	setBrush(color);
    setPen(QPen(Qt::NoPen));

	/* init our shape */
	setShape(0.0f);

	/* timer handling */
	connect(&fadeOutTimer_, SIGNAL(timeout()), this, SLOT(timeout()));
}

void ActuatorView::actuatorUpdate(QList<qreal> actuatorNeurons)
{
	if( actuatorNeurons.length() == 1 ) {
		setShape(actuatorNeurons[0]);

		fadeOutThrusterValue_ = actuatorNeurons[0];
		fadeOutTimer_.start(50);
	}
}

void ActuatorView::setShape(qreal thrusterValue)
{
	/* create our basic shape */
	QPolygonF shape;
	shape << QPointF(-thrusterValue, 0.0f) << QPointF(0.0f, -0.1f) << QPointF(0.0f, 0.1f);

	/* adept our model's shape */
	setPolygon(shape);
}

void ActuatorView::timeout()
{
	fadeOutThrusterValue_ *= 0.8;
	fadeOutThrusterValue_ -= 0.005;

	if ( fadeOutThrusterValue_ > 0.0f ) {
		setShape(fadeOutThrusterValue_);
	} else {
		setShape(0.0f);
		fadeOutTimer_.stop();
	}
}
