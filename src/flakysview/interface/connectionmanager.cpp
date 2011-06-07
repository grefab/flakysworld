#include "connectionmanager.h"
#include "constants.h"

ConnectionManager::ConnectionManager(QObject* parent) :
	QThread(parent)
{
	/* make sure initateConnection cannot be called yet */
	locker_.lock();

	qRegisterMetaType< Thing::Model >("Thing::Model");

	moveToThread(this);

	start();
}

ConnectionManager::~ConnectionManager()
{
	/* do not process further events. */
	quit();

	/* wait for our processing to be finished. */
	wait();
}

void ConnectionManager::run()
{
	/* we need a tcp connection to the outside world */
	tcpClient_ = new TcpClient(this);

	/* get notified of anything the tcp server wants to tell us */
	connect(tcpClient_, SIGNAL(dataArrived(QVariantMap)), this, SLOT(dataArrived(QVariantMap)));
	connect(tcpClient_, SIGNAL(connected()), this, SLOT(connected()));
	connect(tcpClient_, SIGNAL(disconnected()), this, SLOT(disconnected()));

	/* now it's safe to call initiateConnection. */
	locker_.unlock();

	QThread::run();
}


void ConnectionManager::initiateConnection()
{
	/* to avoid race condition in the construction phase. */
	locker_.lock();
	locker_.unlock();

	/* call tcpclient asynchronously to ensure thread safety */
	QMetaObject::invokeMethod(
				tcpClient_,
				"start",
				Qt::QueuedConnection,
				Q_ARG(QString, "localhost"),
				Q_ARG(int, 2345)
				);
}

void ConnectionManager::connected()
{
	/* register on flakysworld server */
	QVariantMap map;
	map.insert(KEY_TYPE, TYPE_REGISTER)	;
	map.insert(KEY_CONCERNS, CONCERNS_WORLD);

	tcpClient_->sendLine(map);

	/* push flaky a bit, so we see action! */
	map.clear();
	QVariantMap actuators;
	QVariantList actuatorNeurons;
	actuatorNeurons.append("0.3");
	actuators.insert("thrl", actuatorNeurons);
	map.insert(KEY_TYPE, TYPE_ACTUATORINPUT);
	map.insert(KEY_BEING, "flaky");
	map.insert(KEY_BEINGS_ACTUATORS, actuators);

	tcpClient_->sendLine(map);
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
