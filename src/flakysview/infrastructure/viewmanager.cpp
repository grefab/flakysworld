#include "viewmanager.h"
#include "gui/views/thingview.h"
#include <QGraphicsView>

ViewManager::ViewManager(QGraphicsScene& scene, QObject *parent) :
	QObject(parent),
	scene_(scene)
{
}

void ViewManager::newThingArrived(const Thing* thing)
{
	ThingView* thingView = new ThingView(*thing);

	/* note that scene takes ownership of thingView. */
	scene_.addItem( thingView );

	foreach(QGraphicsView* view, scene_.views()) {
		view->fitInView(scene_.sceneRect(), Qt::KeepAspectRatio);
	}
}
