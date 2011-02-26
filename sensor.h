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

	QPointF position() const { return position_; }
	qreal rotation() const { return rotation_; }

	void setMapToWorld(QTransform mapToWorld) { mapToWorld_ = mapToWorld; }
	QTransform mapToWorld() { return mapToWorld_; }

public slots:
	void setPosition(const QPointF &position) { position_ = position; }
	void setRotation(qreal rotation) { rotation_ = rotation; }

protected:
	const World& world_;

private:
	QString id_;

	QPointF position_;
	qreal rotation_;

	QTransform mapToWorld_;
};

#endif // SENSOR_H
