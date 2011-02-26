#ifndef BODY_H
#define BODY_H

static const float PI = 3.14159265359;

#include <QObject>
#include <QString>
#include <Box2D.h>
#include <QPointF>

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

public:
	QPointF position() const;
	qreal rotation() const;

	void addFixture(const b2FixtureDef& fixtureDef);
	const b2Fixture* fixture() const;

	QString id() const;
	void setId(QString newId);

signals:
	/* a view can connect to this to take care for updates */
	void changedPosition(QPointF position, qreal rotation);

protected slots:
	void simulationStep();

	/* here comes the stuff a controller needs to manipulate a body */
	void applyForce(const QPointF& force, const QPointF& localPoint);

protected:
	b2World *world_;
	b2Body *body_;
	b2Fixture* fixture_;

private:
	QString id_;
};

#endif // BODY_H
