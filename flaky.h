#ifndef FLAKY_H
#define FLAKY_H

#include <QObject>
#include "polygonbody.h"
#include "bodycontroller.h"


class Flaky : public QObject
{
	Q_OBJECT
public:
	explicit Flaky(QObject *parent = 0);
	~Flaky();

	PolygonBody* body();

signals:
	/* is emitted when visual input changes */
	void seeing();

public slots:
	void accelerate(qreal leftThruster, qreal rightThruster);

protected:
	PolygonBody* body_;
	BodyController* bodyController_;

};

#endif // FLAKY_H
