#include "viewmanager.h"
#include "gui/views/thingview.h"
#include "gui/views/eyeview.h"
#include "gui/views/actuatorview.h"
#include <QGraphicsView>

ViewManager::ViewManager(QGraphicsScene& scene, QObject *parent) :
    QObject(parent),
    scene_(scene)
{
//	scene_.setBackgroundBrush(QBrush(Qt::black));
}

void ViewManager::newThingArrived(const Thing* thing)
{
    ThingView* thingView = new ThingView(*thing);

    /* note that scene takes ownership of thingView. */
    scene_.addItem( thingView );

    /* take care for flaky's sensors and actuators */
    if ( thing->id() == "flaky" ) {
        /* when adding with parent eyeview is automatically added to the scene. */
        EyeView* eyeView = new EyeView(thingView);
        connect(this, SIGNAL(eyeUpdate(QList<qreal>)), eyeView, SLOT(retinaUpdated(QList<qreal>)));

        /* these are our thrusters */
        ActuatorView* avThrottleLeft = new ActuatorView(QPointF(-0.3f, 0.2f), thingView);
        connect(this, SIGNAL(throttleLeftUpdate(QList<qreal>)), avThrottleLeft, SLOT(actuatorUpdate(QList<qreal>)));

        ActuatorView* avThrottleRight = new ActuatorView(QPointF(-0.3f, -0.2f), thingView);
        connect(this, SIGNAL(throttleRightUpdate(QList<qreal>)), avThrottleRight, SLOT(actuatorUpdate(QList<qreal>)));
    }

    foreach(QGraphicsView* view, scene_.views()) {
        view->fitInView(scene_.sceneRect(), Qt::KeepAspectRatio);
    }
}

void ViewManager::actuatorUpdate(QString actuatorId, QList<qreal> actuatorNeurons)
{
    if ( actuatorId == "thrl" ) {
        emit throttleLeftUpdate(actuatorNeurons);
    }

    if ( actuatorId == "thrr" ) {
        emit throttleRightUpdate(actuatorNeurons);
    }
}
