#ifndef FLAKY_H
#define FLAKY_H

#include <QObject>
#include "being/being.h"
#include "bodycontroller.h"
#include <QVariant>

class World;

class Flaky : public Being
{
	Q_OBJECT
public:
	explicit Flaky(World* world, QObject *parent = 0);
	~Flaky();

public slots:
	void accelerate(qreal leftThruster, qreal rightThruster) const;

protected:
	BodyController* bodyController_;

private:
	Body* setupBody(World* world);
};

#endif // FLAKY_H
