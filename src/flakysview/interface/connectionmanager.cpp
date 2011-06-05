#include "connectionmanager.h"
#include "constants.h"

ConnectionManager::ConnectionManager(QObject* parent) :
	QObject(parent)
{
	connect(&tcpClient_, SIGNAL(dataArrived(QVariantMap)), this, SLOT(dataArrived(QVariantMap)));
}

void ConnectionManager::dataArrived(QVariantMap data)
{
	if( data.value(KEY_TYPE).toString() == TYPE_THING ) {

	}
}
