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
	void dataArrived(QVariant data);

protected slots:
	void publish(QVariant data);
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
