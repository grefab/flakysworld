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
    void sensorUpdate(QString sensorId, QList<qreal> sensorNeurons);

signals:
    /* used to forward signals to eye and actuators */
    void eyeUpdated(QList<qreal> sensorNeurons);
    void throttleLeftUpdated(QList<qreal> actuatorNeurons);
    void throttleRightUpdated(QList<qreal> actuatorNeurons);

private:
    QGraphicsScene& scene_;

};

#endif // VIEWMANAGER_H
