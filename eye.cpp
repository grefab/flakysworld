#include "eye.h"
#include <QTransform>


Eye::Eye(World* world, qreal lengthOfSight, QObject *parent) :
	QObject(parent),
	world_(world),
	lengthOfSight_(lengthOfSight)
{

	/* create 9 rays that form a 90° angle in total */
	for( int i = 0; i < 9; ++i ) {
		const qreal rotation = -45.0f + (i * 11.25f);
		addRay(lengthOfSight_, rotation);
	}
}

void Eye::performSensing(QPointF position, qreal rotation)
{
	/* the rays are sent from the origin (0,0) and have to be translated
	 * and rotated to reflect the real world's position.
	 */
	QTransform trans;
	trans.translate(position.x(), position.y());

	QTransform rot;
	rot.rotate(rotation);

	QVariantList output;

	foreach(QLineF ray, rays_) {
		QLineF transformedRay = trans.map(rot.map(ray));
		World::RayHit hitpoint = world_->rayCast(transformedRay);

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
