#include "circlebody.h"

CircleBody::CircleBody(World* world, QPointF position, qreal radius, Body::Type type, QObject *parent) :
		Body(world, position, 0, type, parent),
		radius_(radius)
{
	/* The shape of our body */
	b2CircleShape shapeDef;
	shapeDef.m_radius = radius;

	/* Fixture is the physical representation of a shape */
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shapeDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.2f;

	addFixture(fixtureDef);
}

qreal CircleBody::radius() const {
	return radius_;
}
