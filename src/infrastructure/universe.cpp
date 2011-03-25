#include "universe.h"
#include "bodies/circlebody.h"
#include "bodies/polygonbody.h"
#include "flaky/flaky.h"

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

void Universe::setup()
{
	/* build a cage */
	QPolygonF edgePoly;
	edgePoly <<
			QPointF(0.0f, 0.5f) <<
			QPointF(0.0f, -0.5f);

	PolygonBody* bodyLeft = new PolygonBody(world_, QPointF(-0.5f, 0.0f), 0, edgePoly, Body::Static);
	PolygonBody* bodyRight = new PolygonBody(world_, QPointF(0.5f, 0.0f), 0, edgePoly, Body::Static);
	PolygonBody* bodyTop = new PolygonBody(world_, QPointF(0.0f, 0.5f), PI / 2.0f, edgePoly, Body::Static);
	PolygonBody* bodyBottom = new PolygonBody(world_, QPointF(0.0f, -0.5f), PI / 2.0f, edgePoly, Body::Static);

	world_->addBody(bodyLeft);
	world_->addBody(bodyRight);
	world_->addBody(bodyTop);
	world_->addBody(bodyBottom);

	/* finally, build a set of other things. */
	for (int i = 0; i < 100; ++i) {
		CircleBody* circleBody = new CircleBody(
				world_,
				QPointF(
						-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f,
						-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f
						),
				0.02f,
				Body::Dynamic);
		world_->addBody(circleBody);
	}
}

void Universe::addBeing(Being* being)
{
	beings_.insert(being->id(), being);
}
