#include "tcpserver.h"

TcpServer::TcpServer(quint16 port, QObject *parent) :
	QTcpServer(parent)
{
	listen(QHostAddress::Any, port);

	connect(this, SIGNAL(newConnection()), this, SLOT(socketConnected()));
}

void TcpServer::socketConnected()
{
	/* take and manage the new connection */
	QTcpSocket *socket = nextPendingConnection();
	sockets_.insert(socket);

	connect(socket, SIGNAL(readyRead()), this, SLOT(socketDataAvailable()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

	emit newConnection(socket);
}

void TcpServer::socketDataAvailable()
{
	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

	/* if we have a complete line, pass it on! */
	while ( socket->canReadLine() ) {
		QByteArray line = socket->readLine().trimmed();

		QVariant parsedData = variantBinaryConverter_.toVariant(line);

		emit dataArrived(socket, parsedData.toMap());
	}
}

void TcpServer::socketDisconnected()
{
	/* clean up on socket disconnect */
	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
	sockets_.remove(socket);
	socket->deleteLater();

	emit disconnected(socket);
}

void TcpServer::publish(QVariant data, QTcpSocket* socket)
{
	/* perform serialization */
	QByteArray binaryData = variantBinaryConverter_.toByteArray(data);

	/* tell socket! */
	socket->write(binaryData);

	/* newline tells that data is finished. */
	socket->write("\n");
}
