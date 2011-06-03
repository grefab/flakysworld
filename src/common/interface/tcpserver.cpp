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

		/* perform some consistency checks first to ignore HTTP stuff. */
		if ( !looksLikeJSON(line) ) {
			continue;
		}

		/* convert JSON to something we can handle */
		bool ok;
		QVariant parsedData = parser_.parse(line, &ok);

		if ( !ok ) {
			/* we have a problem. */
			qDebug() << "Error parsing raw data. Assumed JSON.";
			return;
		}

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

void TcpServer::publish(QVariantMap data, QTcpSocket* socket)
{
	/* perform serialization */
	QByteArray binaryData = serializer_.serialize(data);

	/* tell socket! */
	socket->write(binaryData);

	/* newline tells that data is finished. */
	socket->write("\n");
}

bool TcpServer::looksLikeJSON(const QByteArray& data)
{
	/* no data? no json. */
	if ( data.size() <= 0 ) {
		return false;
	}

	/* let's hope there's nothing except json that is included in curly brackets. */
	if (data.at(0) != '{' || data.at(data.size()-1) != '}') {
		return false;
	}

	/* if we reach this point, it seems we have a JSON object. */
	return true;
}
