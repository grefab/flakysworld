#include "viewmanager.h"
#include "gui/views/thingview.h"
#include "gui/views/eyeview.h"
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
		EyeView* eyeView = new EyeView(thingView);
		connect(this, SIGNAL(eyeUpdate(QList<qreal>)), eyeView, SLOT(retinaUpdated(QList<qreal>)));
		scene_.addItem( eyeView );
	}

	foreach(QGraphicsView* view, scene_.views()) {
		view->fitInView(scene_.sceneRect(), Qt::KeepAspectRatio);
	}
}
