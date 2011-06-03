#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QThread>
#include <QTcpSocket>
#include <QVariant>
#include <QSet>
#include "infrastructure/universe.h"
#include "tcpserver.h"
#include "entityserializer.h"


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

private:
	Universe* universe_;
	TcpServer* tcpServer_;

	EntitySerializer entitySerializer_;

	QSet<QTcpSocket*> neuronReceivers_;
	QSet<QTcpSocket*> worldReceivers_;
};

#endif // CONNECTIONMANAGER_H
