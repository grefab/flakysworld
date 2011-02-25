#ifndef EYE_H
#define EYE_H

#include <QObject>
#include "world.h"
#include "QVariant"
#include <QPointF>
#include <QList>
#include <QLineF>

class Eye : public QObject
{
	Q_OBJECT
public:
	explicit Eye(World* world, qreal lengthOfSight, QObject *parent = 0);

signals:
	void hasSeen(QVariant output);

public slots:
	/* we need te position and orientation of the eye */
	void performSensing(QPointF position, qreal rotation);

protected:
	typedef QList<QLine> Rays;

	Rays rays_;
	World* world_;
	qreal lengthOfSight_;
};

#endif // EYE_H
