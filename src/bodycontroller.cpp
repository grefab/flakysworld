#include "bodycontroller.h"
#include <QTransform>

BodyController::BodyController(Body* body, QObject* parent) :
		QObject(parent),
		body_(body)
{
	connect(this, SIGNAL(applyForce(QPointF,QPointF)), body_, SLOT(applyForce(QPointF,QPointF)));
}

void BodyController::push(const QPointF& force, const QPointF& localPoint)
{
	QTransform transformation;
	transformation.rotateRadians(body_->rotation());

	QPointF appliedForce = transformation.map(force);

	emit applyForce(appliedForce, localPoint);
}
