#include "polygonbody.h"

PolygonBody::PolygonBody(QPointF position, qreal rotation, QPolygonF polygon, QObject *parent) :
		Body(position, rotation, parent),
		polygon_(polygon)
{
	bodyDef_.type = b2_staticBody;


	/* The shape of our body */
	int n = polygon_.size();
	b2Vec2 vertices[n];
	for ( int i = 0; i < n; ++i ) {
		const QPointF &p = polygon_.at(i);
		vertices[i].Set(p.x(), p.y());
	}
	shapeDef_.Set(vertices, n);

	/* Fixture is the physical representation of a shape */
	fixtureDef_.shape = &shapeDef_;
	fixtureDef_.density = 1.0f;
	fixtureDef_.friction = 0.5f;
	fixtureDef_.restitution = 0.2f;
}

QPolygonF PolygonBody::polygon() const {
	return polygon_;
}
