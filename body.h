#ifndef BODY_H
#define BODY_H

static const float PI = 3.14159265359;

#include <QObject>
#include <QString>
#include <Box2D.h>
#include <QPointF>

#include <QDebug>

class Body : public QObject
{
	Q_OBJECT

protected:
	explicit Body(QPointF position, qreal rotation, QObject *parent = 0);

public:
	void setWorld(b2World* world);

	QPointF position() const;
	qreal rotation() const;

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

	b2BodyDef bodyDef_;
	b2FixtureDef fixtureDef_;

private:
	QString id_;
};

#endif // BODY_H
