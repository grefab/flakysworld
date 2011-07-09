#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	~Client();
	void start(QHostAddress address, quint16 port);

public slots:
	void connected();
	void send(QByteArray data);

private:
	QTcpSocket socket;

};

#endif // CLIENT_H
