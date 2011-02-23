#ifndef CIRCLEBODY_H
#define CIRCLEBODY_H

#include "body.h"

class CircleBody : public Body
{
public:
	CircleBody(World* world, QPointF position, qreal radius, Body::Type type, QObject *parent = 0);

	qreal radius() const;

protected:
	qreal radius_;

};

#endif // CIRCLEBODY_H
