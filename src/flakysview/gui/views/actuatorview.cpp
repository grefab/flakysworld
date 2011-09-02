#include "actuatorview.h"
#include <QBrush>
#include <QPen>

ActuatorView::ActuatorView(QString id, QPointF position, QGraphicsItem *parent) :
	QGraphicsPolygonItem(parent),
	id_(id)
{
	/* locate */
	setPos(position);

	/* colorize! */
	setBrush(Qt::transparent);
	setPen(QPen(QColor(Qt::red)));

	/* init our shape */
	setShape(0.0f);
}

void ActuatorView::actuatorUpdate(QList<qreal> actuatorNeurons)
{
	if( actuatorNeurons.length() == 1 ) {
		setShape(actuatorNeurons[0]);
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
