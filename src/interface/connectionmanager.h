#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QThread>
#include <QTcpSocket>
#include <QVariant>
#include <QSet>
#include "infrastructure/universe.h"
#include "tcpserver.h"
#include "neuronserializer.h"


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

	/* this is for connecting to tcp server */
	void newConnection(QTcpSocket* socket);
	void disconnected(QTcpSocket* socket);
	void dataArrived(QTcpSocket* socket, QVariant data);

protected:
	void run();

private:
	Universe* universe_;
	TcpServer* tcpServer_;

	NeuronSerializer neuronSerializer_;

	QSet<QTcpSocket*> neuronReceivers_;
};

#endif // CONNECTIONMANAGER_H
