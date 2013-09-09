#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include "thing/thing.h"

class ActuatorView;

class ViewManager : public QObject
{
    Q_OBJECT

public:
    explicit ViewManager(QGraphicsScene& scene, QObject *parent = 0);

public slots:
    void newThingArrived(const Thing* thing);
    void actuatorUpdate(QString actuatorId, QList<qreal> actuatorNeurons);

signals:
    /* used to forward signals to eye and actuators */
    void eyeUpdate(QList<qreal> sensorNeurons);
    void throttleLeftUpdate(QList<qreal> actuatorNeurons);
    void throttleRightUpdate(QList<qreal> actuatorNeurons);

private:
    QGraphicsScene& scene_;

};

#endif // VIEWMANAGER_H
