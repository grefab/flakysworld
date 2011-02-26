#include "eye.h"
#include <QTransform>


Eye::Eye(const World& world, const QPointF position, qreal rotation, qreal lengthOfSight, QObject *parent) :
	Sensor(world, position, rotation, parent),
	lengthOfSight_(lengthOfSight)
{

	/* create 9 rays that form a 90° angle in total */
	for( int i = 0; i < 9; ++i ) {
		const qreal rotation = -45.0f + (i * 11.25f);
		addRay(lengthOfSight_, rotation);
	}
}

void Eye::performSensing() const
{
	/* the rays are sent from the origin (0,0) and have to be translated
	 * and rotated to reflect the real world's position.
	 */
	QList<qreal> output;

	foreach(QLineF ray, rays_) {
		QLineF transformedRay = mapToWorld().map(ray);
		World::RayHit hitpoint = world_.rayCast(transformedRay);

		output.append(hitpoint.fraction);
	}

	/* tell anybody who is interested what we have seen */
	emit hasSeen(output);
}

void Eye::addRay(qreal length, qreal rotation)
{
	const QPointF origin = QPointF(0, 0);
	const QPointF destination = QPointF(length, 0.0f);

	QTransform rot;
	rot.rotate(rotation);

	rays_.append(QLineF(origin, rot.map(destination)));
}
