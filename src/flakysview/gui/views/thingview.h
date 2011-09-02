#ifndef THINGVIEW_H
#define THINGVIEW_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include "thing/thing.h"

class ThingView : public QObject, public QGraphicsPolygonItem
{
	Q_OBJECT

public:
	ThingView(const Thing& thing, QGraphicsItem *parent = 0);

private slots:
	void bodyChanged(QTransform transformation);

};

#endif // THINGVIEW_H
