#include "client.h"

#include "client.h"
#include <QHostAddress>

#include <QDebug>

Client::Client(QObject* parent) :
	QObject(parent),
	wantConnection_(false)
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

void Client::start(QHostAddress address, quint16 port)
{
	wantConnection_ = true;

	address_ = address;
	port_ = port;

	qDebug() << "connecting...";
	socket.connectToHost(address, port);
}

void Client::stop()
{
	wantConnection_ = false;
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
}

void Client::disconnected()
{
	qDebug() << "disconnected.";

	if ( wantConnection_ )
		retry();
}

void Client::error(QAbstractSocket::SocketError socketError)
{
	qDebug() << "error" << socketError;

	if ( wantConnection_ )
		retry();
}

void Client::retry()
{
	qDebug() << "retrying in 3 seconds...";
	sleep(3);
	socket.connectToHost(address_, port_);
}
