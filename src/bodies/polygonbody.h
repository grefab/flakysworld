#ifndef POLYGONBODY_H
#define POLYGONBODY_H

#include "body.h"
#include <QPolygonF>

class PolygonBody : public Body
{
public:
	PolygonBody(const World* world, QPointF position, qreal rotation, QPolygonF polygon, Body::Type type, QObject *parent = 0);

	QPolygonF polygon() const;

protected:
	QPolygonF polygon_;

};

#endif // POLYGONBODY_H
