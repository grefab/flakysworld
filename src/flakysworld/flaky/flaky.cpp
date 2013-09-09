#include "flaky.h"
#include "bodies/body.h"
#include <QPolygonF>
#include "eye.h"
#include "thruster.h"

const qreal SCALE = 10.0f;

Flaky::Flaky(World* world, QObject *parent) :
        Being(world, setupBody(world), "flaky", parent)
{
    /* create an eye */
    Eye* eye = new Eye(*this, QPointF(0.03f * SCALE, 0.0f * SCALE), 0, 0.6f * SCALE, "eye", this);
    addSensor(eye);

    /* create our thrusters */
    Thruster* thrl = new Thruster(*this, QPointF(-0.03f * SCALE, 0.03f * SCALE), 0, "thrl", this);
    Thruster* thrr = new Thruster(*this, QPointF(-0.03f * SCALE, -0.03f * SCALE), 0, "thrr", this);
    addActuator(thrl);
    addActuator(thrr);
}

Body* Flaky::setupBody(World* world)
{
    /* set up our shape */
    QPolygonF flakyPoly;
    flakyPoly <<
            QPointF(0.06f * SCALE, 0.0f * SCALE) <<
            QPointF(-0.03f * SCALE, 0.03f * SCALE) <<
            QPointF(-0.03f * SCALE, -0.03f * SCALE);

    /* make it a body */
    Body* body = new Body(world, flakyPoly, QPointF(0, 0), 0.0f, Body::Dynamic, "flaky");

    return body;
}

Flaky::~Flaky()
{
}
