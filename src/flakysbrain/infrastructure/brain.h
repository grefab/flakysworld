#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>

class Brain : public QObject
{
    Q_OBJECT

signals:
    void actuatorUpdated(QString actuatorId, QList<qreal> actuatorNeurons);

public slots:
    void sensorUpdate(QString sensorId, QList<qreal> sensorNeurons);

public:
    explicit Brain(QObject *parent = 0);

};

#endif // BRAIN_H
