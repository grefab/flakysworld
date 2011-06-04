#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QVariant>
#include "interface/variantbinaryconverter.h"

class TcpServer : public QTcpServer
{
	Q_OBJECT

public:
	explicit TcpServer(quint16 port, QObject *parent = 0);

signals:
	void dataArrived(QTcpSocket* socket, QVariantMap data);
	void newConnection(QTcpSocket* socket);
	void disconnected(QTcpSocket* socket);

public slots:
	void send(QVariant data, QTcpSocket* socket);

protected slots:
	void socketConnected();
	void socketDisconnected();
	void socketDataAvailable();

protected:
	QSet<QTcpSocket*> sockets_;

private:
	VariantBinaryConverter variantBinaryConverter_;

};

#endif // TCPSERVER_H
