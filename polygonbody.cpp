#include "polygonbody.h"

PolygonBody::PolygonBody(World* world, QPointF position, qreal rotation, QPolygonF polygon, Body::Type type, QObject *parent) :
		Body(world, position, rotation, type, parent),
		polygon_(polygon)
{
	/* The shape of our body */
	b2PolygonShape shapeDef;

	int n = polygon_.size();
	b2Vec2 vertices[n];
	for ( int i = 0; i < n; ++i ) {
		const QPointF &p = polygon_.at(i);
		vertices[i].Set(p.x(), p.y());
	}
	shapeDef.Set(vertices, n);

	/* Fixture is the physical representation of a shape */
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shapeDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.2f;

	addFixture(fixtureDef);
}

QPolygonF PolygonBody::polygon() const {
	return polygon_;
}
