#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include "tcpclient.h"
#include "thing/thing.h"
#include "interface/entityserializer.h"

class ConnectionManager : public QObject
{
	Q_OBJECT
public:
	explicit ConnectionManager(QObject* parent = 0);

	void initiateConnection();

signals:
	void thingUpdate(Thing::Model thingModel);

protected slots:
	void connected();
	void disconnected();
	void dataArrived(QVariantMap data);

private:
	TcpClient tcpClient_;
	EntitySerializer entitySerializer_;
};

#endif // CONNECTIONMANAGER_H
