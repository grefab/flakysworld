#include "flaky.h"
#include "world.h"
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

	/* we need to adjust our sensors when the body has moved. */
	connect(body_, SIGNAL(changedPosition(QTransform)), this, SLOT(bodyMoved(QTransform)));

	/* when the world has changed, we want new sensor input. */
	connect(world, SIGNAL(worldChanged()), this, SLOT(worldChanged()));
}

Flaky::~Flaky()
{
	delete bodyController_;
	delete body_;
}

PolygonBody* Flaky::body() const
{
	return body_;
}

QList<Sensor*> Flaky::sensors() const
{
	return sensors_.values();
}

void Flaky::accelerate(qreal leftThruster, qreal rightThruster)
{
	/* left thruster */
	bodyController_->push(QPointF(leftThruster, 0), QPointF(-0.03, 0.03));

	/* right thruster */
	bodyController_->push(QPointF(rightThruster, 0), QPointF(-0.03, -0.03));
}

void Flaky::bodyMoved(QTransform transformation)
{
	/* we need our sensors to know about their position in the world. */
	foreach(Sensor* sensor, sensors_) {
		sensor->setMapToWorld(transformation);
	}
}

void Flaky::worldChanged()
{
	/* something, not necessary ourselves, changed. update sensors! */
	foreach(Sensor* sensor, sensors_) {
		sensor->performSensing();
	}
}
