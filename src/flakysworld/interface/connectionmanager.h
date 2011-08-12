#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QThread>
#include <QTcpSocket>
#include <QVariant>
#include <QSet>
#include "infrastructure/universe.h"
#include "interface/tcpserver.h"
#include "interface/entityserializer.h"
#include "thing/thing.h"

class ConnectionManager : public QThread
{
	Q_OBJECT
public:
	explicit ConnectionManager(Universe* universe, QObject *parent = 0);
	~ConnectionManager();

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

	void sendCompleteWorld(QTcpSocket* socket);

private:
	void handleActuatorinput(const QVariantMap& data);
	void handleRegister(const QVariantMap& data, QTcpSocket* socket);
	void handleUnregister(const QVariantMap& data, QTcpSocket* socket);

	Universe* universe_;
	TcpServer* tcpServer_;

	EntitySerializer entitySerializer_;

	QSet<QTcpSocket*> neuronReceivers_;
	QSet<QTcpSocket*> worldReceivers_;
};

#endif // CONNECTIONMANAGER_H
