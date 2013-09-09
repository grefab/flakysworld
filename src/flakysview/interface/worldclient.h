#ifndef WORLDCLIENT_H
#define WORLDCLIENT_H

#include <QThread>
#include "tcpclient.h"
#include "thing/thing.h"
#include "interface/entityserializer.h"

class WorldClient : public QThread
{
    Q_OBJECT
public:
    explicit WorldClient(QObject* parent = 0);
    ~WorldClient();

    void initiateConnection();

signals:
    void thingUpdate(Thing::Model thingModel);
    void eyeUpdate(QList<qreal> sensorNeurons);
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

#endif // WORLDCLIENT_H
