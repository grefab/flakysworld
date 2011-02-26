#include "eyeview.h"

EyeView::EyeView(const Eye& eye, QGraphicsItem *parent) :
		QGraphicsObject(parent),
		eye_(eye)
{
	connect(&eye, SIGNAL(hasSeen(QList<qreal>)), this, SLOT(retinaUpdated(QList<qreal>)));
}

void EyeView::retinaUpdated(QList<qreal> output)
{

}
