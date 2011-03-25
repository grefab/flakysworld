#include "body.h"
#include "infrastructure/world.h"

Body::Body(const World* world, QPolygonF shape, QPointF position, qreal rotation, Body::Type type, QObject *parent) :
		Thing(shape, position, rotation, parent),
		world_(world->world())
{
	/* b2Body is an abstract entity of an element in the physics world */
	b2BodyDef bodyDef;

	switch(type) {
	case Static:
		bodyDef.type = b2_staticBody;
		break;
	case Dynamic:
		bodyDef.type = b2_dynamicBody;
	}

	bodyDef.position.Set(position.x(), position.y()); // bring in sync with QGraphisObject rotation
	bodyDef.angle = rotation; // bring in sync with QGraphisObject rotation

	bodyDef.linearDamping = 0.2f;
	bodyDef.angularDamping = 0.2f;

	/* so we can be found e.g. by ray casts */
	bodyDef.userData = this;

	/* bring ourselves into the world */
	body_ = world_->CreateBody(&bodyDef);


	/* take care for Box2D's fixture */
	/* The shape of our body */
	b2PolygonShape shapeDef;

	int n = shape.size();
	b2Vec2 vertices[n];
	for ( int i = 0; i < n; ++i ) {
		const QPointF &p = shape.at(i);
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

Body::~Body()
{
	world_->DestroyBody(body_);
}

QPointF Body::getPosition() const
{
	const b2Vec2& position = body_->GetPosition();

	return QPointF(position.x, position.y);
}

qreal Body::getRotation() const
{
	return body_->GetAngle();
}

b2Fixture* Body::addFixture(const b2FixtureDef& fixtureDef)
{
	return body_->CreateFixture(&fixtureDef);
}

void Body::simulationStepHappened()
{
	/* only update when we need */
	if( body_->IsAwake() ) {
		update(getPosition(), getRotation());

		emit changedPosition(getWorldMap());
	}
}

void Body::applyForce(const QPointF& force, const QPointF& localPoint)
{
	/* calculate directed force */
	QTransform transformation;
	transformation.rotateRadians(rotation());
	QPointF directedForce = transformation.map(force);

	/* convert to b2Vec2 */
	b2Vec2 b2Force(directedForce.x(), directedForce.y());
	b2Vec2 b2LocalPoint(localPoint.x(), localPoint.y());

	/* finally apply */
	body_->ApplyForce(b2Force, body_->GetWorldPoint(b2LocalPoint));
}
