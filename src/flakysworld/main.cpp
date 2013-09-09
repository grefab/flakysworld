#include <QtGui>

#include "infrastructure/universe.h"

#include "interface/connectionmanager.h"

ConnectionManager* setupIO(Universe* universe)
{
    ConnectionManager* connectionManager = new ConnectionManager(universe);

    return connectionManager;
}

int main(int argc, char *argv[])
{
    QCoreApplication* app = new QCoreApplication(argc, argv);

    /* our universe. it manages world and engine that keeps world alive. */
    Universe* universe = new Universe();

    /* start neuron IO */
    ConnectionManager* connectionManager = setupIO(universe);

    /* preparation is done. let if flow! */
    qDebug() << "started.";
    return app->exec();

    /* when we reach this, the program is finished. delete everything in reverse order. */
    delete connectionManager;
    delete universe;
    delete app;
}
