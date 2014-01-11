#include <QApplication>

#include "interface/universeclient.h"
#include "infrastructure/brain.h"
#include "controllers/engine.h"
#include "gui/surface.h"


UniverseClient* setupIO(Brain* brain)
{
    UniverseClient* universeClient = new UniverseClient();

    QObject::connect(universeClient, SIGNAL(sensorUpdated(QString,QList<qreal>)), brain, SLOT(sensorUpdate(QString,QList<qreal>)));
    QObject::connect(brain, SIGNAL(actuatorUpdated(QString,QList<qreal>)), universeClient, SLOT(actuatorUpdate(QString,QList<qreal>)));

    return universeClient;
}

int main(int argc, char *argv[])
{
//    QCoreApplication app = new QCoreApplication(argc, argv);
    QApplication app(argc, argv);
    Surface surface;
    surface.show();

    /* brain contains a collection of things */
    Brain* brain = new Brain();

    /* engine drives brain */
    Engine engine(&app);
    QObject::connect(&engine, SIGNAL(finished()), &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL(aboutToQuit()), &engine, SLOT(terminate()));
    engine.start();

    /* start neuron IO */
    UniverseClient* universeClient = setupIO(brain);
    universeClient->initiateConnection();

    /* preparation is done. let if flow! */
    qDebug() << "started.";
    int returnValue = app.exec();

    engine.quit();
    engine.wait();

    /* when we reach this, the program is finished. delete everything in reverse order. */
    delete universeClient;
    delete brain;

    return returnValue;
}
