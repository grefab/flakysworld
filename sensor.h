#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QString>
#include <QPointF>

class World;

class Sensor : public QObject
{
	Q_OBJECT
public:
	explicit Sensor(const World& world, QObject *parent = 0);

	/* we need the position and orientation of the eye */
	virtual void performSensing() const =0;

	QString id() const;

private:
	QString id_;
	const World& world_;
};

#endif // SENSOR_H
