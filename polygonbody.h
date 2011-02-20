#ifndef POLYGONBODY_H
#define POLYGONBODY_H

#include "body.h"
#include <QPolygonF>

class PolygonBody : public Body
{
public:
	PolygonBody(QPointF position, qreal rotation, QPolygonF polygon, QObject *parent = 0);

	QPolygonF polygon() const;

protected:
	QPolygonF polygon_;

private:
	b2PolygonShape shapeDef_;
};

#endif // POLYGONBODY_H
