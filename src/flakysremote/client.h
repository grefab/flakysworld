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
	void stop();

public slots:
	void connected();
	void disconnected();
	void error(QAbstractSocket::SocketError socketError);
	void send(QByteArray data);

private:
	void retry();

	QHostAddress address_;
	quint16 port_;
	QTcpSocket socket;
	bool wantConnection_;

};

#endif // CLIENT_H
