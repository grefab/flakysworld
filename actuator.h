#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "organ.h"

class Actuator : public Organ
{
	Q_OBJECT
public:
	explicit Actuator(const World& world, const QPointF position, qreal rotation, QString id = "", QObject *parent = 0);

public slots:
	virtual void receiveInput(QList<qreal> input) =0;

};

#endif // ACTUATOR_H
