#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QThread>
#include "tcpclient.h"
#include "thing/thing.h"
#include "interface/entityserializer.h"

class ConnectionManager : public QThread
{
	Q_OBJECT
public:
	explicit ConnectionManager(QObject* parent = 0);
	~ConnectionManager();

	void initiateConnection();

signals:
	void thingUpdate(Thing::Model thingModel);

protected slots:
	void connected();
	void disconnected();
	void dataArrived(QVariantMap data);

protected:
	void run();

private:
	TcpClient* tcpClient_;
	EntitySerializer entitySerializer_;

};

#endif // CONNECTIONMANAGER_H
