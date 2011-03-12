#include "being.h"
#include "world.h"
#include "sensor.h"

Being::Being(World* world, Body* body, QObject *parent) :
	QObject(parent),
	world_(*world),
	body_(body)
{
}

Being::~Being()
{
	delete body_;
}

void Being::addSensor(Sensor *sensor)
{
	/* store it for management */
	sensors_.insert(sensor->id(), sensor);

	/* we need to adjust our sensors when the body has moved. */
	connect(body_, SIGNAL(changedPosition(QTransform)), sensor, SLOT(setMapParentToWorld(QTransform)));

	/* when the world has changed, we want new sensor input. */
	connect(&world_, SIGNAL(worldChanged()), sensor, SLOT(performSensing()));
}
