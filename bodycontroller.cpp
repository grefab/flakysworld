#include "bodycontroller.h"
#include <QTransform>

BodyController::BodyController(Body* body, QObject* parent) :
		QObject(parent),
		body_(body)
{
	connect(this, SIGNAL(applyForce(QPointF,QPointF)), body_, SLOT(applyForce(QPointF,QPointF)));
}

void BodyController::push()
{
	QPointF impulse(0.01f, 0);
	QTransform transformation;
	transformation.rotateRadians(body_->rotation());

	QPointF appliedPulse = transformation.map(impulse);

	emit applyForce(appliedPulse, QPointF(0, 0.02f));
	emit applyForce(appliedPulse, QPointF(0, -0.02f));
}
