#ifndef BODY_H
#define BODY_H

static const float PI = 3.14159265359;

#include <QObject>
#include <QString>
#include <Box2D.h>
#include <QPointF>
#include <QTransform>

class World;

class Body : public QObject
{
	Q_OBJECT

public:
	enum Type {
		Static,
		Dynamic
	};

protected:
	/* protected constructor, so only inheriting classes can access it. this way
	 * this class can not be instaciated directly.
	 */
	explicit Body(const World* world, QPointF position, qreal rotation, Type type = Dynamic, QObject *parent = 0);

public:
	~Body();

	/* tell us that a simulation step has happened and something may have changed. */
	void simulationStepHappened();

	QPointF position() const;
	qreal rotation() const;

	void setId(QString newId);
	QString id() const;

	bool isAwake() const { return body_->IsAwake(); }

	QTransform getWorldMap() const { return mapToWorld_; }

signals:
	/* a view can connect to this to take care for updates */
	void changedPosition(QTransform transformation) const;

protected slots:
	/* here comes the stuff a controller needs to manipulate a body */
	void applyForce(const QPointF& force, const QPointF& localPoint);

protected:
	b2Fixture* addFixture(const b2FixtureDef& fixtureDef);

private:
	QString id_;
	b2World *world_;
	b2Body *body_;

	void updateMapToWorld();
	QTransform mapToWorld_;
};

#endif // BODY_H
