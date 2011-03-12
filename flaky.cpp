#include "flaky.h"
#include "polygonbody.h"
#include <QPolygonF>
#include "eye.h"

Flaky::Flaky(World* world, QObject *parent) :
		Being(world, setupBody(world), parent)
{
	/* let us be able to control the body */
	bodyController_ = new BodyController(body());

	/* create an eye */
	Eye* eye = new Eye(*world, QPointF(0.059f, 0.0f), 0, 0.6f, "eye", this);
	addSensor(eye);
}

Body* Flaky::setupBody(World* world)
{
	/* set up our shape */
	QPolygonF flakyPoly;
	flakyPoly <<
			QPointF(0.06f, 0.0f) <<
			QPointF(-0.03f, 0.03f) <<
			QPointF(-0.03f, -0.03f);

	/* make it a body */
	Body* body = new PolygonBody(world, QPointF(0, 0), 0.0f, flakyPoly, Body::Dynamic);
	body->setId("flaky");

	return body;
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
