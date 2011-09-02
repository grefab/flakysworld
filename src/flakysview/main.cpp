#include <QtGui>

#include "gui/surface.h"
#include "gui/views/thingview.h"
//#include "gui/views/eyeview.h"

#include "infrastructure/world.h"
#include "interface/connectionmanager.h"
#include "infrastructure/viewmanager.h"

Surface* setupGUI(World* world, ConnectionManager* connectionManager)
{
	Surface* surface = new Surface();

	/* viewmanager handles updates of things */
	ViewManager* viewManager = new ViewManager(*surface->scene(), surface);

	QObject::connect(world, SIGNAL(newThingArrived(const Thing*)), viewManager, SLOT(newThingArrived(const Thing*)));
	QObject::connect(connectionManager, SIGNAL(eyeUpdate(QList<qreal>)), viewManager, SIGNAL(eyeUpdate(QList<qreal>)));


	/* build a corresponding view for flaky's eyes. */
//	foreach(Sensor* sensor, universe->being("flaky")->sensors()) {
//		Eye* eye = dynamic_cast<Eye*>(sensor);
//		if ( eye ) {
//			surface->scene()->addItem( new EyeView(*eye) );
//		}
//	}

	/* show everything */
	surface->view()->fitInView(surface->scene()->sceneRect(), Qt::KeepAspectRatio);

	/* connect our key events */
//	QObject::connect(surface->view(), SIGNAL(keyPressed(Qt::Key)), universe, SLOT(keyPressHandler(Qt::Key)));
//	QObject::connect(surface->view(), SIGNAL(keyReleased(Qt::Key)), universe, SLOT(keyReleaseHandler(Qt::Key)));

	/* and our engage button */
	// TODO: Just provide motoric information and let flaky handle the consequences.
//	QObject::connect(surface, SIGNAL(engageTriggered(qreal,qreal)), universe, SLOT(thurstersHandler(qreal,qreal)));

	/* show everything */
	surface->show();

	return surface;
}

ConnectionManager* setupIO(World* world)
{
	ConnectionManager* connectionManager = new ConnectionManager();

	QObject::connect(connectionManager, SIGNAL(thingUpdate(Thing::Model)), world, SLOT(thingUpdated(Thing::Model)));

	return connectionManager;
}

int main(int argc, char *argv[])
{
	QApplication* app = new QApplication(argc, argv);

	/* world contains a collection of things */
	World* world = new World();

	/* start neuron IO */
	ConnectionManager* connectionManager = setupIO(world);
	connectionManager->initiateConnection();

	/* make everything visible */
	Surface* surface = setupGUI(world, connectionManager);

	/* preparation is done. let if flow! */
	return app->exec();

	/* when we reach this, the program is finished. delete everything in reverse order. */
	delete surface;
	delete connectionManager;
	delete world;
	delete app;
}
