#ifndef BODYVIEW_H
#define BODYVIEW_H

#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include "bodies/body.h"
#include <QPointF>

class BodyView : public QObject, public QAbstractGraphicsShapeItem
{
	Q_OBJECT

public:
	BodyView(const Body& body, QGraphicsItem *parent = 0);

protected:
	const Body& body_;

private slots:
	void bodyChanged(QTransform transformation);

};

#endif // BODYVIEW_H
