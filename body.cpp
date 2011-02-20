#include "body.h"
#include <QUuid>

Body::Body(QPointF position, qreal rotation, QObject *parent) :
	QObject(parent),
	world_(NULL)
{
	id_ = QUuid::createUuid().toString();

	/* b2Body is an abstract entity of an element in the physics world */
	bodyDef_.type = b2_dynamicBody;
	bodyDef_.position.Set(position.x(), position.y()); // bring in sync with QGraphisObject rotation
	bodyDef_.angle = rotation; // bring in sync with QGraphisObject rotation

	bodyDef_.linearDamping = 0.2f;
	bodyDef_.angularDamping = 0.2f;
}

void Body::setWorld(b2World *world)
{
	if ( world_ ) {
		/* clean up our previous assignment */
		world_->DestroyBody(body_);
	}

	/* Bring our above definitions into the world */
	world_ = world;
	body_ = world_->CreateBody(&bodyDef_);
	body_->CreateFixture(&fixtureDef_);
}

QPointF Body::position() const
{
	const b2Vec2& position = body_->GetPosition();

	return QPointF(position.x, position.y);
}

qreal Body::rotation() const
{
	return body_->GetAngle();
}

void Body::setStatic()
{
	bodyDef_.type = b2_staticBody;
}

QString Body::id() const
{
	return id_;
}

void Body::setId(QString newId)
{
	id_ = newId;
}

void Body::simulationStep()
{
	if( body_->IsAwake() ) {
		emit changedPosition(position(), rotation());
	}
}

void Body::applyForce(const QPointF& force, const QPointF& localPoint)
{
	b2Vec2 b2Force(force.x(), force.y());
	b2Vec2 b2LocalPoint(localPoint.x(), localPoint.y());

	body_->ApplyForce(b2Force, body_->GetWorldPoint(b2LocalPoint));
}
