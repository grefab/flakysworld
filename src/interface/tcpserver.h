#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>

class TcpServer : public QTcpServer
{
	Q_OBJECT

public:
	explicit TcpServer(quint16 port, QObject *parent = 0);

signals:
	void dataArrived(QByteArray data);

protected slots:
	void publish(QByteArray data);
	void socketConnected();
	void socketDisconnected();
	void socketDataAvailable();

protected:
	QSet<QTcpSocket*> sockets_;
};

#endif // TCPSERVER_H
