#include "universe.h"
#include "bodies/body.h"
#include "flaky/flaky.h"
#include "being/sensor.h"

#include <QDebug>

Universe::Universe(QObject *parent) :
		QObject(parent)
{
	world_ = new World();
	engine_ = new Engine(world_);

	/* set up the elements in the world */
	setup();

	/* put flaky into the world! */
	addBeing(new Flaky(world_));

	/* put everything in motion */
	engine_->start();
}

Universe::~Universe()
{
	delete engine_;

	foreach(Being* being, beings()) {
		delete being;
	}

	delete world_;
}

void Universe::keyPressHandler(Qt::Key key)
{
	Q_UNUSED(key);

	thurstersHandler(0.05f, 0.05f);
}

void Universe::keyReleaseHandler(Qt::Key key)
{
	Q_UNUSED(key);
}

void Universe::thurstersHandler(qreal leftThruster, qreal rightThruster)
{
	/* prepare neuron data */
	QList<qreal> leftNeuronValues;
	leftNeuronValues.append(leftThruster);
	QList<qreal> rightNeuronValues;
	rightNeuronValues.append(rightThruster);

	/* engage flaky's thursters */
	actuatorRefresh("flaky", "thrl", leftNeuronValues);
	actuatorRefresh("flaky", "thrr", rightNeuronValues);
}

void Universe::actuatorRefresh(QString beingId, QString actuatorId, QList<qreal> neuronValues)
{
	Being* being = beings_.value(beingId);

	if ( !being ) {
		qDebug() << "being" << beingId << "not found.";
		return;
	}

	/* call the actuator update asynchronously */
	QMetaObject::invokeMethod(
				being,
				"actuatorRefresh",
				Qt::QueuedConnection,
				Q_ARG(QString, actuatorId),
				Q_ARG(QList<qreal>, neuronValues)
				);
}

void Universe::sensorSensed(QList<qreal> sensorNeurons)
{
	const Sensor* sensor = static_cast<Sensor*>(sender());
	const QString sensorId = sensor->id();
	const QString beingId = sensor->being().id();

	emit sensorDataAvaliable(beingId, sensorId, sensorNeurons);
}

void Universe::setup()
{
	/* build a cage */
	QPolygonF edgePoly;
	edgePoly <<
			QPointF(0.0f, 0.5f) <<
			QPointF(0.0f, -0.5f);

	Body* bodyLeft = new Body(world_, edgePoly, QPointF(-0.5f, 0.0f), 0, Body::Static);
	Body* bodyRight = new Body(world_, edgePoly, QPointF(0.5f, 0.0f), 0, Body::Static);
	Body* bodyTop = new Body(world_, edgePoly, QPointF(0.0f, 0.5f), PI / 2.0f, Body::Static);
	Body* bodyBottom = new Body(world_, edgePoly, QPointF(0.0f, -0.5f), PI / 2.0f, Body::Static);

	world_->addBody(bodyLeft);
	world_->addBody(bodyRight);
	world_->addBody(bodyTop);
	world_->addBody(bodyBottom);

	/* finally, build a set of other things. */
	QPolygonF regularPoly;

	/* construct regular polygons */
	{
		const int edges = 6;
		const qreal radius = 0.03;

		QTransform rotationMap;
		QPointF edge(0, radius);
		for ( int i = 0; i < edges; ++i ) {
			regularPoly << rotationMap.map(edge);
			rotationMap.rotate( (qreal)360 / (qreal)edges );
		}
	}

	/* distribute a lot of them everywhere */
	for (int i = 0; i < 100; ++i) {
		Body* body = new Body(
				world_,
				regularPoly,
				QPointF(
						-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f,
						-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f
						),
				0,
				Body::Dynamic);
		world_->addBody(body);
	}
}

void Universe::addBeing(Being* being)
{
	beings_.insert(being->id(), being);

	foreach(Sensor* sensor, being->sensors()) {
		QObject::connect(sensor, SIGNAL(updated(QList<qreal>)), this, SLOT(sensorSensed(QList<qreal>)));
	}

}
