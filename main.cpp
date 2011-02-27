#include <QtGui>

#include "surface.h"
#include "universe.h"
#include "circlebodyview.h"
#include "polygonbodyview.h"
#include "eyeview.h"

Surface* setupGUI(Universe* universe)
{
	Surface* surface = new Surface();
	surface->show();

	QObject::connect(universe->engine(), SIGNAL(updatedFPS(int)), surface->fpsLabel(), SLOT(setNum(int)));

	/* build a corresponding view for each body. */
	foreach(Body* body, universe->world()->bodies()) {
		CircleBody* circleBody = dynamic_cast<CircleBody*>(body);
		if ( circleBody ) {
			surface->scene()->addItem( new CircleBodyView(*circleBody) );
		}

		PolygonBody* polygonBody = dynamic_cast<PolygonBody*>(body);
		if ( polygonBody ) {
			surface->scene()->addItem( new PolygonBodyView(*polygonBody) );
		}
	}

	/* build a corresponding view for flaky's sensors. */
	foreach(Sensor* sensor, universe->flaky()->sensors()) {
		Eye* eye = dynamic_cast<Eye*>(sensor);
		if ( eye ) {
			surface->scene()->addItem( new EyeView(*eye) );
		}
	}

	/* show everything */
	surface->view()->fitInView(surface->scene()->sceneRect(), Qt::KeepAspectRatio);

	/* connect our key events */
	QObject::connect(surface->view(), SIGNAL(keyPressed(Qt::Key)), universe, SLOT(keyPressHandler(Qt::Key)));
	QObject::connect(surface->view(), SIGNAL(keyReleased(Qt::Key)), universe, SLOT(keyReleaseHandler(Qt::Key)));

	/* and our engage button */
	// TODO: Just provide motoric information and let flaky handle the consequences.
	QObject::connect(surface, SIGNAL(engageTriggered(qreal,qreal)), universe->flaky(), SLOT(accelerate(qreal,qreal)));

	return surface;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(time(0));

	/* our universe. it manages world and engine that keeps world alive. */
	Universe* universe = new Universe();

	/* make everything visible */
	Surface* surface = setupGUI(universe);

	/* preparation is done. let if flow! */
	return app.exec();

	delete surface;
	delete universe;
}
