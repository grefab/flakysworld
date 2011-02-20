#ifndef CIRCLEBODY_H
#define CIRCLEBODY_H

#include "body.h"

class CircleBody : public Body
{
public:
	CircleBody(QPointF position, qreal radius, QObject *parent = 0);

	qreal radius() const;

protected:
	qreal radius_;

private:
	b2CircleShape shapeDef_;
};

#endif // CIRCLEBODY_H
