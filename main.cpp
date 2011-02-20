#include <Box2D.h>
#include <QDebug>
#include <QtGui>
#include <QGLWidget>

#include "graphicsview.h"
#include "world.h"
#include "engine.h"
#include "universe.h"
#include "circlebodyview.h"
#include "polygonbodyview.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	qsrand(time(0));

	QGraphicsScene scene;
	scene.setItemIndexMethod(QGraphicsScene::NoIndex);
	scene.setBackgroundBrush(Qt::white);
	scene.setSceneRect(-1, -1, 2, 2);

	GraphicsView view(&scene);

	/* greatly enhances speed. */
	view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
//	view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	view.setRenderHint(QPainter::Antialiasing);
	view.scale(400, 400);
	view.show();

	/* our engine! it takes care for the bodies we give to it. */
	World* world = new World();
	Engine* engine = new Engine(world);
	Universe* universe = new Universe(world, engine);

	foreach(Body* body, world->bodies()) {
		CircleBody* circleBody = dynamic_cast<CircleBody*>(body);
		if ( circleBody ) {
			scene.addItem( new CircleBodyView(*circleBody) );
		}

		PolygonBody* polygonBody = dynamic_cast<PolygonBody*>(body);
		if ( polygonBody ) {
			scene.addItem( new PolygonBodyView(*polygonBody) );
		}
	}

/*
	scene.addItem(new PolygonBodyView(*bodyLeft));
	scene.addItem(new PolygonBodyView(*bodyRight));
	scene.addItem(new PolygonBodyView(*bodyTop));
	scene.addItem(new PolygonBodyView(*bodyBottom));
	scene.addItem( new PolygonBodyView(*flaky.body()) );

	CircleBodyView* circleBodyView = new CircleBodyView(*circleBody);
	scene.addItem(circleBodyView);
*/

	engine->start();

	return app.exec();
}
