#ifndef FLAKY_H
#define FLAKY_H

#include <QObject>
#include "polygonbody.h"
#include "bodycontroller.h"
#include <QVariant>
#include <QHash>
#include <QList>
#include "sensor.h"

class World;

class Flaky : public QObject
{
	Q_OBJECT
public:
	explicit Flaky(World* world, QObject *parent = 0);
	~Flaky();

	PolygonBody* body() const;
	QList<Sensor*> sensors() const;

public slots:
	void accelerate(qreal leftThruster, qreal rightThruster);

protected:
	PolygonBody* body_;
	BodyController* bodyController_;

	QHash<QString, Sensor*> sensors_;

private slots:
	void bodyMoved(QTransform transformation);
	void worldChanged();

};

#endif // FLAKY_H
