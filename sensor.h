#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QString>
#include <QPointF>
#include <QTransform>

class World;

class Sensor : public QObject
{
	Q_OBJECT

public:
	explicit Sensor(const World& world, const QPointF position, qreal rotation, QObject *parent = 0);

	/* we need the position and orientation of the eye */
	virtual void performSensing() const =0;

	QString id() const;

	void setMapParentToWorld(QTransform mapParentToWorld);
	const QTransform& mapToWorld() const;

signals:
	void positionChanged(QTransform mapToWorld);

protected:
	const World& world_;

private:
	QString id_;

	QPointF position_;
	qreal rotation_;

	QTransform mapToParent_;
	QTransform mapParentToWorld_;
	void updateMapToWorld();
	QTransform mapToWorld_;
};

#endif // SENSOR_H
