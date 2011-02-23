#ifndef FLAKY_H
#define FLAKY_H

#include <QObject>
#include "polygonbody.h"
#include "bodycontroller.h"
#include <QVariant>

class World;

class Flaky : public QObject
{
	Q_OBJECT
public:
	explicit Flaky(World* world, QObject *parent = 0);
	~Flaky();

	PolygonBody* body();

signals:
	/* is emitted when sensorical input changes */
	void sensorsUpdated( QVariant sensorData );

public slots:
	void accelerate(qreal leftThruster, qreal rightThruster);

	/* so we can update our sensors */
	void worldChanged();

protected:
	PolygonBody* body_;
	BodyController* bodyController_;

private:
	QVariant useEyes();

};

#endif // FLAKY_H
