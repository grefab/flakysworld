#ifndef EYE_H
#define EYE_H

#include <QObject>
#include "sensor.h"
#include "world.h"
#include <QList>
#include <QLineF>

class Eye : public Sensor
{
	Q_OBJECT

public:
	explicit Eye(const World& world, const QPointF position, qreal rotation, qreal lengthOfSight, QObject *parent = 0);

	/* we need the position and orientation of the eye */
	void performSensing() const;

	const QList<QLineF>& rays() const { return rays_; }

signals:
	void hasSeen(QList<qreal> output) const;

protected:
	void addRay(qreal length, qreal rotation);

private:
	QList<QLineF> rays_;
	qreal lengthOfSight_;
};

#endif // EYE_H
