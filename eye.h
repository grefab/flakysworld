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
	explicit Eye(qreal lengthOfSight, QObject *parent = 0);

signals:
	void hasSeen(QList<qreal> output) const;

protected:
	/* we need the position and orientation of the eye */
	void performSensing(const World& world, QPointF position, qreal rotation) const;

	void addRay(qreal length, qreal rotation);

private:
	QList<QLineF> rays_;
	qreal lengthOfSight_;
};

#endif // EYE_H
