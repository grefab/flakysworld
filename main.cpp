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

	/* build a corresponding view for each body */
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

	/* connect our key events */
	QObject::connect(&view, SIGNAL(keyPressed(Qt::Key)), universe, SLOT(keyPressHandler(Qt::Key)));
	QObject::connect(&view, SIGNAL(keyReleased(Qt::Key)), universe, SLOT(keyReleaseHandler(Qt::Key)));

	/* preparation is done. let if flow! */
	return app.exec();
}
