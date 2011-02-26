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
	explicit Body(World* world, QPointF position, qreal rotation, Type type = Dynamic, QObject *parent = 0);
	~Body();

public:
	/* tell us that a simulation step has happened and something may have changed. */
	void simulationStepHappened() const;

	QPointF position() const;
	qreal rotation() const;

	void setId(QString newId);
	QString id() const;

	QPointF getWorldPoint(const QPointF& localPoint) const;
	QTransform getWorldMap() const;

signals:
	/* a view can connect to this to take care for updates */
	void changedPosition(QPointF position, qreal rotation) const;

protected slots:
	/* here comes the stuff a controller needs to manipulate a body */
	void applyForce(const QPointF& force, const QPointF& localPoint);

protected:
	b2Fixture* addFixture(const b2FixtureDef& fixtureDef);

private:
	QString id_;
	b2World *world_;
	b2Body *body_;

};

#endif // BODY_H
