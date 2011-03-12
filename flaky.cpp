#include "flaky.h"
#include "polygonbody.h"
#include <QPolygonF>
#include "eye.h"

Flaky::Flaky(World* world, QObject *parent) :
		Being(world, parent)
{
	/* set up our shape */
	QPolygonF flakyPoly;
	flakyPoly <<
			QPointF(0.06f, 0.0f) <<
			QPointF(-0.03f, 0.03f) <<
			QPointF(-0.03f, -0.03f);

	/* make it a body */
	body_ = new PolygonBody(world, QPointF(0, 0), 0.0f, flakyPoly, Body::Dynamic);
	body_->setId("flaky");

	/* let us be able to control the body */
	bodyController_ = new BodyController(body_);

	/* create an eye */
	Eye* eye = new Eye(*world, QPointF(0.059f, 0.0f), 0, 0.6f, "eye", this);
	addSensor(eye);
}

Flaky::~Flaky()
{
	delete bodyController_;
}

void Flaky::accelerate(qreal leftThruster, qreal rightThruster)
{
	/* left thruster */
	bodyController_->push(QPointF(leftThruster, 0), QPointF(-0.03, 0.03));

	/* right thruster */
	bodyController_->push(QPointF(rightThruster, 0), QPointF(-0.03, -0.03));
}
