#include "eye.h"
#include <QTransform>


Eye::Eye(const Being& being, const QPointF position, qreal rotation, qreal lengthOfSight, QString id, QObject *parent) :
	Sensor(being, position, rotation, id, parent),
	lengthOfSight_(lengthOfSight)
{
	const qreal visionDegrees = 90;
	const int rayCount = 32;

	/* create rayCount rays that form a visionDegrees° angle in total */
	for( int i = 0; i < rayCount; ++i ) {
		const qreal rotation = -visionDegrees / 2.0f + ((qreal)i * (visionDegrees / (qreal)(rayCount -1)));
		addRay(lengthOfSight_, rotation);
	}
}

void Eye::performSensing() const
{
	/* the rays are sent from the origin (0,0) and have to be translated
	 * and rotated to reflect the real world's position.
	 */
	QList<qreal> output;

	/* create list of rays we need to cast */
	QList<QLineF> transformedRays;
	foreach(QLineF ray, rays_) {
		QLineF transformedRay = mapToWorld().map(ray);
		transformedRays.append(transformedRay);
	}

	/* perform ray casting for all rays */
	QList<World::RayHit> hitpoints = being_.world().rayCast(transformedRays);

	/* create our result */
	foreach(World::RayHit hitpoint, hitpoints) {
		output.append(hitpoint.fraction);
	}

	/* tell anybody who is interested what we have seen */
	updateIfNeeded(output);
}

void Eye::addRay(qreal length, qreal rotation)
{
	const QPointF origin = QPointF(0, 0);
	const QPointF destination = QPointF(length, 0.0f);

	QTransform rot;
	rot.rotate(rotation);

	rays_.append(QLineF(origin, rot.map(destination)));
}
