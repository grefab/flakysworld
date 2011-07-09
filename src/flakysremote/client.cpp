#include "client.h"

#include "client.h"
#include <QHostAddress>

#include <QDebug>

Client::Client(QObject* parent) :
	QObject(parent)
{
  connect(&socket, SIGNAL(connected()),
	this, SLOT(connected()));

  qDebug() << "created";
}

Client::~Client()
{
  socket.close();
}

void Client::start(QHostAddress address, quint16 port)
{
  qDebug() << "connecting...";
  socket.connectToHost(address, port);
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
