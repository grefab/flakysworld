#ifndef UNIVERSECLIENT_H
#define UNIVERSECLIENT_H

#include <QThread>
#include "tcpclient.h"
#include "thing/thing.h"
#include "entityserializer.h"

class UniverseClient : public QThread
{
    Q_OBJECT
public:
    explicit UniverseClient(QObject* parent = 0);
    ~UniverseClient();

    void initiateConnection();

signals:
    void thingUpdated(Thing::Model thingModel);
    void eyeUpdated(QList<qreal> sensorNeurons);
    void actuatorUpdated(QString actuatorId, QList<qreal> actuatorNeurons);

public slots:
    void actuatorUpdate(QString actuatorId, QList<qreal> actuatorNeurons);

protected slots:
    void connected();
    void disconnected();
    void dataArrived(QVariantMap data);

protected:
    void run();

private:
    void registerForWorld();
    void registerForSensors();
    void registerForActuators();
    void pushFlaky();

    TcpClient* tcpClient_;
    EntitySerializer entitySerializer_;

    QMutex locker_;
};

#endif // UNIVERSECLIENT_H
