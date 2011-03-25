#ifndef BODY_H
#define BODY_H

static const float PI = 3.14159265359;

#include <Box2D.h>
#include "thing.h"


class World;

class Body : public Thing
{
	Q_OBJECT

public:
	enum Type {
		Static,
		Dynamic
	};

	explicit Body(const World* world, QPolygonF shape, QPointF position, qreal rotation, Type type = Dynamic, QObject *parent = 0);
	~Body();

	/* tell us that a simulation step has happened and something may have changed. */
	void simulationStepHappened();

	/* pushes the body */
	void applyForce(const QPointF& force, const QPointF& localPoint);

signals:
	/* a view can connect to this to take care for updates */
	void changedPosition(QTransform transformation) const;

protected:
	b2Fixture* addFixture(const b2FixtureDef& fixtureDef);

private:
	bool isAwake() const { return body_->IsAwake(); }
	QPointF getPosition() const;
	qreal getRotation() const;

	b2World *world_;
	b2Body *body_;

};

#endif // BODY_H
