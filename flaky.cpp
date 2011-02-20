#include "flaky.h"
#include <QPolygonF>

Flaky::Flaky(QObject *parent) :
	QObject(parent)
{
	QPolygonF flakyPoly;
	flakyPoly <<
			QPointF(0.06f, 0.0f) <<
			QPointF(-0.03f, 0.03f) <<
			QPointF(-0.03f, -0.03f);

	body_ = new PolygonBody(QPointF(0, 0), 0.0f, flakyPoly);
	body_->setId("flaky");
}

Flaky::~Flaky()
{
}

PolygonBody* Flaky::body()
{
	return body_;
}
