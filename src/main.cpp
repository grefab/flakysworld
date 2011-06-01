#include <QtGui>

#include "infrastructure/universe.h"

#include "gui/surface.h"
#include "gui/views/thingview.h"
#include "gui/views/eyeview.h"

#include "interface/connectionmanager.h"

Surface* setupGUI(Universe* universe)
{
	Surface* surface = new Surface();
	surface->show();

	QObject::connect(universe->engine(), SIGNAL(updatedFPS(int)), surface->fpsLabel(), SLOT(setNum(int)));

	/* build a corresponding view for each body. */
	foreach(Body* body, universe->world()->bodies()) {
		surface->scene()->addItem( new ThingView(*body) );
	}

	/* build a corresponding view for flaky's eyes. */
	foreach(Sensor* sensor, universe->being("flaky")->sensors()) {
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
	QObject::connect(surface, SIGNAL(engageTriggered(qreal,qreal)), universe, SLOT(thurstersHandler(qreal,qreal)));

	return surface;
}

ConnectionManager* setupIO(Universe* universe)
{
	ConnectionManager* connectionManager = new ConnectionManager(universe);

	return connectionManager;
}

int main(int argc, char *argv[])
{
	const bool useGui = true;

	QCoreApplication* app;
	if ( useGui ) {
		app = new QApplication(argc, argv);
	} else {
		app = new QCoreApplication(argc, argv);
	}

	/* our universe. it manages world and engine that keeps world alive. */
	Universe* universe = new Universe();

	/* make everything visible */
	Surface* surface = 0;
	if ( useGui ) surface = setupGUI(universe);

	/* start neuron IO */
	ConnectionManager* connectionManager = setupIO(universe);

	/* preparation is done. let if flow! */
	return app->exec();

	/* when we reach this, the program is finished. delete everything in reverse order. */
	delete connectionManager;
	delete surface;
	delete universe;
	delete app;
}
