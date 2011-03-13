#ifndef BODYCONTROLLER_H
#define BODYCONTROLLER_H

#include <QObject>
#include "body.h"

class BodyController : public QObject
{
	Q_OBJECT

public:
	BodyController(Body* body, QObject* parent = 0);

	void push(const QPointF& force, const QPointF& localPoint);

signals:
	void applyForce(const QPointF& force, const QPointF& localPoint);

protected:
	Body* body_;
};

#endif // BODYCONTROLLER_H
