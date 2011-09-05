#include "client.h"

#include "client.h"
#include <QHostAddress>

#include <QDebug>

Client::Client(QHostAddress address, quint16 port, QObject* parent) :
	QObject(parent),
	address_(address),
	port_(port),
	wantConnection_(false),
	retrying_(false)
{
	connect(&socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(&socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

	qDebug() << "created";
}

Client::~Client()
{
	stop();
}

void Client::start()
{
	wantConnection_ = true;
	retrying_ = false;

	qDebug() << "connecting...";
	socket.connectToHost(address_, port_);
}

void Client::stop()
{
	wantConnection_ = false;
	retrying_ = false;

	disconnect();
	socket.close();
}

void Client::send(QByteArray data)
{
	data.append("\n");
	qDebug() << "write" << socket.write(data);
}

void Client::connected()
{
	qDebug() << "connected.";
	retrying_ = false;
}

void Client::disconnected()
{
	qDebug() << "disconnected.";

	retry();
}

void Client::error(QAbstractSocket::SocketError socketError)
{
	qDebug() << "error" << socketError;

	retry();
}

void Client::retry()
{
	if ( wantConnection_ && !retrying_ ) {
		qDebug() << "retrying in 3 seconds...";
		retrying_ = true;
		QTimer::singleShot(3000, this, SLOT(start()));
	}
}
