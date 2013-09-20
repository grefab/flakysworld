#include <QCoreApplication>

#include "interface/universeclient.h"
#include "infrastructure/brain.h"

UniverseClient* setupIO(Brain* brain)
{
    UniverseClient* universeClient = new UniverseClient();

    QObject::connect(universeClient, SIGNAL(sensorUpdated(QString,QList<qreal>)), brain, SLOT(sensorUpdate(QString,QList<qreal>)));
    QObject::connect(brain, SIGNAL(actuatorUpdated(QString,QList<qreal>)), universeClient, SLOT(actuatorUpdate(QString,QList<qreal>)));

    return universeClient;
}

int main(int argc, char *argv[])
{
    QCoreApplication* app = new QCoreApplication(argc, argv);

    /* brain contains a collection of things */
    Brain* brain = new Brain();

    /* start neuron IO */
    UniverseClient* universeClient = setupIO(brain);
    universeClient->initiateConnection();

    /* preparation is done. let if flow! */
    qDebug() << "started.";
    return app->exec();

    /* when we reach this, the program is finished. delete everything in reverse order. */
    delete universeClient;
    delete brain;
    delete app;
}
