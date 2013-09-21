#include "being.h"
#include "infrastructure/world.h"
#include "sensor.h"
#include "actuator.h"

#include <QDebug>

Being::Being(World* world, Body* body, QString id, QObject *parent) :
    QObject(parent),
    id_(id),
    world_(world),
    body_(body)
{
    world_->addBody(body_);
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
    connect(world_, SIGNAL(worldChanged()), sensor, SLOT(performSensing()));
}

void Being::addActuator(Actuator *actuator)
{
    /* store it for management */
    actuators_.insert(actuator->id(), actuator);
}

void Being::actuatorRefresh(QString actuatorId, QList<qreal> neuronValues)
{
    Actuator* actuator = actuators_.value(actuatorId);

    if ( !actuator ) {
        qDebug() << "actuator" << actuatorId << "not found in being" << id();
        return;
    }

    /* call the actuator update asynchronously */
    QMetaObject::invokeMethod(
                actuator,
                "receiveInput",
                Qt::QueuedConnection,
                Q_ARG(QList<qreal>, neuronValues)
                );
}
