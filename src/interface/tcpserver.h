#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QVariant>
#include "external/qjson/src/serializer.h"
#include "external/qjson/src/parser.h"

class TcpServer : public QTcpServer
{
	Q_OBJECT

public:
	explicit TcpServer(quint16 port, QObject *parent = 0);

signals:
	void dataArrived(QTcpSocket* socket, QVariant data);
	void newConnection(QTcpSocket* socket);
	void disconnected(QTcpSocket* socket);

public slots:
	void publish(QVariant data, QTcpSocket* socket);

protected slots:
	void socketConnected();
	void socketDisconnected();
	void socketDataAvailable();

protected:
	QSet<QTcpSocket*> sockets_;
	QJson::Serializer serializer_;
	QJson::Parser parser_;

private:
	bool looksLikeJSON(const QByteArray& data);

};

#endif // TCPSERVER_H
