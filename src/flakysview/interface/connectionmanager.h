#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include "tcpclient.h"
#include "thing/thing.h"

class ConnectionManager : public QObject
{
	Q_OBJECT
public:
	explicit ConnectionManager(QObject* parent = 0);

signals:
	void thingUpdate(Thing::Model thingModel);

protected slots:
	void dataArrived(QVariantMap data);

private:
	TcpClient tcpClient_;
};

#endif // CONNECTIONMANAGER_H
