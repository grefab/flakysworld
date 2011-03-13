#ifndef EYE_H
#define EYE_H

#include <QObject>
#include "being/sensor.h"
#include "infrastructure/world.h"
#include <QList>
#include <QLineF>

class Eye : public Sensor
{
	Q_OBJECT

public:
	explicit Eye(const Being& being, const QPointF position, qreal rotation, qreal lengthOfSight, QString id = "", QObject *parent = 0);

	const QList<QLineF>& rays() const { return rays_; }

public slots:
	/* query the world to get sensor data */
	void performSensing() const;

protected:
	void addRay(qreal length, qreal rotation);

private:
	QList<QLineF> rays_;
	qreal lengthOfSight_;

};

#endif // EYE_H
