#ifndef THRUSTER_H
#define THRUSTER_H

#include "being/actuator.h"

class Thruster : public Actuator
{
    Q_OBJECT
public:
    explicit Thruster(const Being& being, const QPointF position, qreal rotation, QString id = "", QObject *parent = 0);

public slots:
    void receiveInput(QList<qreal> input);

};

#endif // THRUSTER_H
