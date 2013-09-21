#include <QtGui>

#include "infrastructure/universe.h"

#include "interface/universeserver.h"

UniverseServer* setupIO(Universe* universe)
{
    UniverseServer* universeServer = new UniverseServer(universe);

    return universeServer;
}

int main(int argc, char *argv[])
{
    QCoreApplication* app = new QCoreApplication(argc, argv);

    /* our universe. it manages world and engine that keeps world alive. */
    Universe* universe = new Universe();

    /* start neuron IO */
    UniverseServer* universeServer = setupIO(universe);

    /* preparation is done. let if flow! */
    qDebug() << "started.";
    return app->exec();

    /* when we reach this, the program is finished. delete everything in reverse order. */
    delete universeServer;
    delete universe;
    delete app;
}
