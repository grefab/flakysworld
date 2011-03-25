#include "flaky.h"
#include "bodies/polygonbody.h"
#include <QPolygonF>
#include "eye.h"
#include "thruster.h"

Flaky::Flaky(World* world, QObject *parent) :
		Being(world, setupBody(world), "flaky", parent)
{
	/* create an eye */
	Eye* eye = new Eye(*this, QPointF(0.059f, 0.0f), 0, 0.6f, "eye", this);
	addSensor(eye);

	/* create our thrusters */
	Thruster* thrl = new Thruster(*this, QPointF(-0.03f, 0.03f), 0, "thrl", this);
	Thruster* thrr = new Thruster(*this, QPointF(-0.03f, -0.03f), 0, "thrr", this);
	addActuator(thrl);
	addActuator(thrr);
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
}
