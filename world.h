#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <Box2D.h>
#include <QHash>
#include "body.h"

class Engine;

class World : public QObject
{
	Q_OBJECT

	friend class Engine;

public:
	explicit World(QObject *parent = 0);
	~World();

	/* we take ownership of the body! */
	Body* addBody(Body* body);

	b2World* world();
	QList<Body*> bodies() const;

	/* this contains the nearest hit from the ray cast origin. */
	struct RayHit
	{
		RayHit(Body* body, QPointF point, qreal fraction) :
				body(body),
				point(point),
				fraction(fraction)
		{}

		Body* body;
		QPointF point;
		qreal fraction;
	};

signals:
	void simulationStepHappened();

protected:
	void performSimulationStep(float32 timestep);
	RayHit rayCast(const QPointF& from, const QPointF& to) const;

	QHash<QString, Body*> bodies_;
	b2World *world_;

private:
	/* so we know about our engine, just used for thread comparison. */
	void setEngine(Engine* engine) { engine_ = engine; }
	Engine* engine_;
};

#endif // WORLD_H
