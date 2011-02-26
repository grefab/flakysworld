#include "eyeview.h"

Eyeview::Eyeview(const Eye& eye, QGraphicsItem *parent) :
	QGraphicsObject(parent),
	eye_(eye)
{
	connect(&eye, SIGNAL(hasSeen(QList<qreal>)), this, SLOT(retinaUpdated(QList<qreal>)));
}

void Eyeview::retinaUpdated(QList<qreal> output)
{

}
