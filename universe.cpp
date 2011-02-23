#include "universe.h"
#include "circlebody.h"
#include "polygonbody.h"

Universe::Universe(QObject *parent) :
	QObject(parent)
{
	world_ = new World();
	engine_ = new Engine(world_);

	flaky_ = new Flaky(world_);

	setup();

	engine_->start();
}

void Universe::keyPressHandler(Qt::Key key)
{
	flaky_->accelerate(0.01, 0.01);
}

void Universe::keyReleaseHandler(Qt::Key key)
{

}


void Universe::setup()
{
	/* build a cage */
	QPolygonF edgePoly;
	edgePoly <<
			QPointF(0.0f, 0.5f) <<
			QPointF(0.0f, -0.5f);

	PolygonBody* bodyLeft = new PolygonBody(world_, QPointF(-0.5f, 0.0f), 0, edgePoly, b2_staticBody);
	PolygonBody* bodyRight = new PolygonBody(world_, QPointF(0.5f, 0.0f), 0, edgePoly, b2_staticBody);
	PolygonBody* bodyTop = new PolygonBody(world_, QPointF(0.0f, 0.5f), PI / 2.0f, edgePoly, b2_staticBody);
	PolygonBody* bodyBottom = new PolygonBody(world_, QPointF(0.0f, -0.5f), PI / 2.0f, edgePoly, b2_staticBody);

	world_->addBody(bodyLeft);
	world_->addBody(bodyRight);
	world_->addBody(bodyTop);
	world_->addBody(bodyBottom);

	/* our little being. jump into the world, flaky! */
	world_->addBody(flaky_->body());

	/* finally, build a set of other things. */
	for (int i = 0; i < 100; ++i) {
		CircleBody* circleBody = new CircleBody(
				world_,
				QPointF(
					-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f,
					-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f
				),
				0.02f,
				b2_dynamicBody);
		world_->addBody(circleBody);
	}
}
