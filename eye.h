#ifndef EYE_H
#define EYE_H

#include <QObject>
#include "world.h"
#include <QPointF>
#include <QList>
#include <QLineF>

class Eye : public QObject
{
	Q_OBJECT
public:
	explicit Eye(World* world, qreal lengthOfSight, QObject *parent = 0);

signals:
	void hasSeen(QList<qreal> output);

protected slots:
	/* we need the position and orientation of the eye */
	void performSensing(QPointF position, qreal rotation);

protected:
	void addRay(qreal length, qreal rotation);

private:
	QList<QLineF> rays_;
	World* world_;
	qreal lengthOfSight_;
};

#endif // EYE_H
