#include <QApplication>
#include <QtGui>

#include "gui/surface.h"
#include "gui/views/thingview.h"
//#include "gui/views/eyeview.h"

#include "infrastructure/world.h"
#include "interface/universeclient.h"
#include "infrastructure/viewmanager.h"

Surface* setupGUI(World* world, UniverseClient* universeClient)
{
    Surface* surface = new Surface();

    /* viewmanager handles updates of things */
    ViewManager* viewManager = new ViewManager(*surface->scene(), surface);

    QObject::connect(world, SIGNAL(newThingArrived(const Thing*)), viewManager, SLOT(newThingArrived(const Thing*)));
    QObject::connect(universeClient, SIGNAL(sensorUpdated(QString,QList<qreal>)), viewManager, SLOT(sensorUpdate(QString,QList<qreal>)));
    QObject::connect(universeClient, SIGNAL(actuatorUpdated(QString,QList<qreal>)), viewManager, SLOT(actuatorUpdate(QString,QList<qreal>)));


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

UniverseClient* setupIO(World* world)
{
    UniverseClient* universeClient = new UniverseClient();

    QObject::connect(universeClient, SIGNAL(thingUpdated(Thing::Model)), world, SLOT(thingUpdate(Thing::Model)));

    return universeClient;
}

int main(int argc, char *argv[])
{
    QApplication* app = new QApplication(argc, argv);

    /* world contains a collection of things */
    World* world = new World();

    /* start neuron IO */
    UniverseClient* universeClient = setupIO(world);
    universeClient->initiateConnection();

    /* make everything visible */
    Surface* surface = setupGUI(world, universeClient);

    /* preparation is done. let if flow! */
    return app->exec();

    /* when we reach this, the program is finished. delete everything in reverse order. */
    delete surface;
    delete universeClient;
    delete world;
    delete app;
}
