#ifndef UNIVERSESERVER_H
#define UNIVERSESERVER_H

#include <QThread>
#include <QTcpSocket>
#include <QVariant>
#include <QSet>
#include "infrastructure/universe.h"
#include "interface/tcpserver.h"
#include "interface/entityserializer.h"
#include "thing/thing.h"

class UniverseServer : public QThread
{
    Q_OBJECT
public:
    explicit UniverseServer(Universe* universe, QObject *parent = 0);
    ~UniverseServer();

signals:
    void actuatorUpdate(QString beingId, QString actuatorId, QList<qreal> actuatorNeurons);

protected slots:
    /* this is to get notified by the outside world */
    void sensorUpdate(QString beingId, QString sensorId, QList<qreal> sensorNeurons);
    void thingUpdate(QString thingId, QPointF position, qreal rotation);

    /* this is for connecting to tcp server */
    void newConnection(QTcpSocket* socket);
    void disconnected(QTcpSocket* socket);
    void dataArrived(QTcpSocket* socket, QVariantMap data);

protected:
    void run();

private:
    void handleActuatorinput(const QVariantMap& data);
    void handleRegister(const QVariantMap& data, QTcpSocket* socket);
    void handleUnregister(const QVariantMap& data, QTcpSocket* socket);

    void sendSensorUpdate(const QString& beingId, const QString& sensorId, const QList<qreal>& sensorNeurons);
    void sendActuatorUpdate(const QString& beingId, const QString& actuatorId, const QList<qreal>& actuatorNeurons);
    void sendThingUpdate(const QString& thingId, const QPointF& position, qreal rotation);
    void sendCompleteWorld(QTcpSocket* socket);

    Universe* universe_;
    TcpServer* tcpServer_;

    EntitySerializer entitySerializer_;

    QSet<QTcpSocket*> sensorReceivers_;
    QSet<QTcpSocket*> actuatorReceivers_;
    QSet<QTcpSocket*> worldReceivers_;
};

#endif // UNIVERSESERVER_H
