#ifndef EYEVIEW_H
#define EYEVIEW_H

#include <QGraphicsObject>
#include "eye.h"
#include <QList>

class EyeView : public QGraphicsObject
{
	Q_OBJECT
public:
	explicit EyeView(const Eye& eye, QGraphicsItem *parent = 0);

protected:
	const Eye& eye_;

private slots:
	void retinaUpdated(QList<qreal> output);
};

#endif // EYEVIEW_H
