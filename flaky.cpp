#include "flaky.h"
#include <QPolygonF>

Flaky::Flaky(World* world, QObject *parent) :
		QObject(parent)
{
	QPolygonF flakyPoly;
	flakyPoly <<
			QPointF(0.06f, 0.0f) <<
			QPointF(-0.03f, 0.03f) <<
			QPointF(-0.03f, -0.03f);

	body_ = new PolygonBody(world, QPointF(0, 0), 0.0f, flakyPoly, Body::Dynamic);
	body_->setId("flaky");

	bodyController_ = new BodyController(body_);
}

Flaky::~Flaky()
{
	delete bodyController_;
	delete body_;
}

PolygonBody* Flaky::body()
{
	return body_;
}

void Flaky::accelerate(qreal leftThruster, qreal rightThruster)
{
	/* left thruster */
	bodyController_->push(QPointF(leftThruster, 0), QPointF(-0.03, 0.03));

	/* right thruster */
	bodyController_->push(QPointF(rightThruster, 0), QPointF(-0.03, -0.03));
}

void Flaky::worldChanged()
{
	emit sensorsUpdated(useEyes());
}

QVariant Flaky::useEyes()
{
	return QVariant();
}
