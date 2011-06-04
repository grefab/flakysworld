#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include "interface/variantbinaryconverter.h"

class TcpClient : public QObject
{
	Q_OBJECT
public:
	explicit TcpClient(QObject *parent = 0);
	~TcpClient();

	void start(QHostAddress address, quint16 port);

signals:
	void dataArrived(QVariantMap data);

public slots:
	void connected();
	void disconnected();

	void sendLine(const QVariant& data);
	void dataAvailable();

private:
	QTcpSocket socket_;
	VariantBinaryConverter variantBinaryConverter_;

};

#endif // TCPCLIENT_H
