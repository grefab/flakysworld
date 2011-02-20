#include <QtGui>

#include "surface.h"
#include "world.h"
#include "engine.h"
#include "universe.h"
#include "circlebodyview.h"
#include "polygonbodyview.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(time(0));

	Surface surface;
	surface.show();

	/* our engine! it takes care for the bodies we give to it. */
	World* world = new World();
	Engine* engine = new Engine(world);
	Universe* universe = new Universe(world, engine);

	QObject::connect(engine, SIGNAL(updateFPS(int)), surface.fpsLabel(), SLOT(setNum(int)));

	/* build a corresponding view for each body */
	foreach(Body* body, world->bodies()) {
		CircleBody* circleBody = dynamic_cast<CircleBody*>(body);
		if ( circleBody ) {
			surface.scene()->addItem( new CircleBodyView(*circleBody) );
		}

		PolygonBody* polygonBody = dynamic_cast<PolygonBody*>(body);
		if ( polygonBody ) {
			surface.scene()->addItem( new PolygonBodyView(*polygonBody) );
		}
	}

	/* connect our key events */
	QObject::connect(surface.view(), SIGNAL(keyPressed(Qt::Key)), universe, SLOT(keyPressHandler(Qt::Key)));
	QObject::connect(surface.view(), SIGNAL(keyReleased(Qt::Key)), universe, SLOT(keyReleaseHandler(Qt::Key)));

	/* preparation is done. let if flow! */
	return app.exec();
}
