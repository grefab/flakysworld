#include <Box2D.h>
#include <QDebug>
#include <QtGui>
#include <QGLWidget>

#include "engine.h"
#include "circlebody.h"
#include "circlebodyview.h"
#include "polygonbody.h"
#include "polygonbodyview.h"


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
	Engine* engine = new Engine();
	engine->start();

	/* build a cage */
	QPolygonF poly;
	poly <<
			QPointF(-0.05f, 0.5f) <<
			QPointF(-0.05f, -0.5f) <<
			QPointF(0.05f, -0.5f) <<
			QPointF(0.05f, 0.5f);

	PolygonBody* bodyLeft = new PolygonBody(QPointF(-0.55f, 0.0f), 0, poly);
	PolygonBody* bodyRight = new PolygonBody(QPointF(0.55f, 0.0f), 0, poly);
	PolygonBody* bodyTop = new PolygonBody(QPointF(0.0f, 0.55f), PI / 2.0f, poly);
	PolygonBody* bodyBottom = new PolygonBody(QPointF(0.0f, -0.55f), PI / 2.0f, poly);

	engine->addBody(bodyLeft);
	engine->addBody(bodyRight);
	engine->addBody(bodyTop);
	engine->addBody(bodyBottom);

	scene.addItem(new PolygonBodyView(*bodyLeft));
	scene.addItem(new PolygonBodyView(*bodyRight));
	scene.addItem(new PolygonBodyView(*bodyTop));
	scene.addItem(new PolygonBodyView(*bodyBottom));

	/* our little being. let's call it flaky */
	CircleBody* flaky = new CircleBody(QPointF(0, 0), 0.04f);
	flaky->setId("flaky");

	engine->addBody(flaky);

	scene.addItem( new CircleBodyView(*flaky) );

	/* finally, build a set of other things. */
	for (int i = 0; i < 10; ++i) {
		CircleBody* circleBody = new CircleBody(
				QPointF(
					-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f,
					-0.5 + ((qreal)qrand() / (qreal)INT_MAX) * 1.0f
				),
				0.02f);
		engine->addBody(circleBody);

		CircleBodyView* circleBodyView = new CircleBodyView(*circleBody);
		scene.addItem(circleBodyView);
	}



	return app.exec();
}
