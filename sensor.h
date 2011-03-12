#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QString>
#include <QPointF>
#include "organ.h"

class Sensor : public Organ
{
	Q_OBJECT

public:
	explicit Sensor(const World& world, const QPointF position, qreal rotation, QString id = "", QObject *parent = 0);

signals:
	void sensed(QList<qreal> output) const;

public slots:
	virtual void performSensing() const =0;

protected:
	void updateIfNeeded(const QList<qreal>& newOutput) const;
	bool isUpdateNeeded(const QList<qreal>& newOutput) const;

private:
	/* really, really private, because we modify this but promise everyone
	 * we are const in updateIfNeeded(). this serves for sending only different output.
	 */
	QList<qreal> lastOutput_;

};

#endif // SENSOR_H
