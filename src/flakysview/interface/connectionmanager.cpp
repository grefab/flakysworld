#include "connectionmanager.h"
#include "constants.h"

ConnectionManager::ConnectionManager(QObject* parent) :
	QObject(parent)
{
	connect(&tcpClient_, SIGNAL(dataArrived(QVariantMap)), this, SLOT(dataArrived(QVariantMap)));
	connect(&tcpClient_, SIGNAL(connected()), this, SLOT(connected()));
	connect(&tcpClient_, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ConnectionManager::initiateConnection()
{
	tcpClient_.start("localhost", 2345);
}

void ConnectionManager::connected()
{
	/* register on flakysworld server */
	QVariantMap map;
	map.insert(KEY_TYPE, TYPE_REGISTER)	;
	map.insert(KEY_CONCERNS, CONCERNS_WORLD);

	tcpClient_.sendLine(map);
}

void ConnectionManager::disconnected()
{

}

void ConnectionManager::dataArrived(QVariantMap data)
{
	if( data.value(KEY_TYPE).toString() == TYPE_THING ) {
		Thing::Model thingModel;
		entitySerializer_.deserializeThing(data, &thingModel.id_, &thingModel.shape_, &thingModel.position_, &thingModel.rotation_);

		emit thingUpdate(thingModel);
	}
}
