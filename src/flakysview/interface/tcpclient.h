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

	void start(QString host, quint16 port);

signals:
	void connected();
	void disconnected();
	void dataArrived(QVariantMap data);

public slots:
	void sendLine(const QVariant& data);
	void dataAvailable();

protected slots:
	void onConnect();
	void onDisconnect();

private:
	QTcpSocket socket_;
	VariantBinaryConverter variantBinaryConverter_;

};

#endif // TCPCLIENT_H
