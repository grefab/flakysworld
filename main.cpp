#include <Box2D.h>
#include <QDebug>
#include <QtGui>
#include <QGLWidget>

#include "world.h"
#include "engine.h"
#include "circlebody.h"
#include "circlebodyview.h"
#include "polygonbody.h"
#include "polygonbodyview.h"
#include "flaky.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	qsrand(time(0));

	QGraphicsScene scene;
	scene.setItemIndexMethod(QGraphicsScene::NoIndex);
	scene.setBackgroundBrush(Qt::white);
	scene.setSceneRect(-1, -1, 2, 2);

	QGraphicsView view(&scene);

	/* greatly enhances speed. */
	view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
//	view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	view.setRenderHint(QPainter::Antialiasing);
	view.scale(400, 400);
	view.show();

	/* our engine! it takes care for the bodies we give to it. */
	World* world = new World();
	Engine* engine = new Engine(world);

	/* build a cage */
	QPolygonF edgePoly;
	edgePoly <<
			QPointF(0.0f, 0.5f) <<
			QPointF(0.0f, -0.5f);

	PolygonBody* bodyLeft = new PolygonBody(QPointF(-0.5f, 0.0f), 0, edgePoly);
	PolygonBody* bodyRight = new PolygonBody(QPointF(0.5f, 0.0f), 0, edgePoly);
	PolygonBody* bodyTop = new PolygonBody(QPointF(0.0f, 0.5f), PI / 2.0f, edgePoly);
	PolygonBody* bodyBottom = new PolygonBody(QPointF(0.0f, -0.5f), PI / 2.0f, edgePoly);

	bodyLeft->setStatic();
	bodyRight->setStatic();
	bodyTop->setStatic();
	bodyBottom->setStatic();

	world->addBody(bodyLeft);
	world->addBody(bodyRight);
	world->addBody(bodyTop);
	world->addBody(bodyBottom);

	scene.addItem(new PolygonBodyView(*bodyLeft));
	scene.addItem(new PolygonBodyView(*bodyRight));
	scene.addItem(new PolygonBodyView(*bodyTop));
	scene.addItem(new PolygonBodyView(*bodyBottom));

	/* our little being. let's call it flaky */
	Flaky flaky;
	world->addBody(flaky.body());
	scene.addItem( new PolygonBodyView(*flaky.body()) );

	/* finally, build a set of other things. */
	for (int i = 0; i < 400; ++i) {
		CircleBody* circleBody = new CircleBody(
				QPointF(
					-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f,
					-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f
				),
				0.02f);
		world->addBody(circleBody);

		CircleBodyView* circleBodyView = new CircleBodyView(*circleBody);
		scene.addItem(circleBodyView);
	}

	engine->start();

	return app.exec();
}
