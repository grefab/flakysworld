#include "circlebody.h"

CircleBody::CircleBody(QPointF position, qreal radius, QObject *parent) :
		Body(position, 0, parent),
		radius_(radius)
{
	/* The shape of our body */
	shapeDef_.m_radius = radius;

	/* Fixture is the physical representation of a shape */
	fixtureDef_.shape = &shapeDef_;
	fixtureDef_.density = 1.0f;
	fixtureDef_.friction = 0.5f;
	fixtureDef_.restitution = 0.008f;
}

qreal CircleBody::radius() const {
	return radius_;
}
