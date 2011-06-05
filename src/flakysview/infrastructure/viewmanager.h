#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include "thing/thing.h"

class ViewManager : public QObject
{
	Q_OBJECT
public:
	explicit ViewManager(QGraphicsScene& scene, QObject *parent = 0);

public slots:
	void newThingArrived(const Thing* thing);

private:
	QGraphicsScene& scene_;
};

#endif // VIEWMANAGER_H
