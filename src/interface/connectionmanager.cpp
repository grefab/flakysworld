#include "connectionmanager.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

JSON Communication Spec
--------
Note that the characters  {}[]":  used here mean the actual characters (map, array,
string delimiters), whereas  ()  group elements as entity.  +*  mean “one or more”
and “zero or more” of the previously described entity (where entities have to be
comma separated).  |  describes a set of optional elements, from which one has to
be chosen.


These objects can be received by flakysworld:

{ "type" : "register",
  "concerns" : ( "sensors" | "world" ) }
{ "type" : "unregister",
  "concerns" : ( "sensors" | "world" ) }
{ "type" : "actuatorinput",
  "being" : "BEING_ID",
  "actuators" : { ( "ACTUATOR_ID" : [ REAL* ] )+ } }


If registered to corresponding updates, a client will recieve:

{ "type" : "sensoroutput",
  "being" : "BEING_ID",
  "sensors" : { ( "SENSOR_ID" : [ REAL* ] )+ } }
{ "type" : "thing",
  "thing" : "THING_ID",
  "shape" : [ ( { "x" : REAL, "y" : REAL } )* ],
  "position" : { "x" : REAL, "y" : REAL },
  "rotation" : REAL }


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


ConnectionManager::ConnectionManager(Universe* universe, QObject *parent) :
	QThread(parent),
	universe_(universe)
{
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
	tcpServer_ = new TcpServer(2345, this);

	/* get notified of anything the tcp server wants to tell us */
	connect(tcpServer_, SIGNAL(newConnection(QTcpSocket*)), this, SLOT(newConnection(QTcpSocket*)));
	connect(tcpServer_, SIGNAL(disconnected(QTcpSocket*)), this, SLOT(disconnected(QTcpSocket*)));
	connect(tcpServer_, SIGNAL(dataArrived(QTcpSocket*,QVariant)), this, SLOT(dataArrived(QTcpSocket*,QVariant)));

	/* notify universe if we have new actuator data */
	connect(this, SIGNAL(actuatorUpdate(QString,QString,QList<qreal>)), universe_, SLOT(actuatorRefresh(QString,QString,QList<qreal>)));

	/* get notified by universe if sensor data updates */
	connect(universe_, SIGNAL(sensorDataAvaliable(QString,QString,QList<qreal>)), this, SLOT(sensorUpdate(QString,QString,QList<qreal>)));

	QThread::run();
}

void ConnectionManager::sensorUpdate(QString beingId, QString sensorId, QList<qreal> sensorNeurons)
{
	/* get a variant to be sent */
	QVariant sendMe = neuronSerializer_.serializeSensor(beingId, sensorId, sensorNeurons);

	/* tell all interested sockets about our sensor */
	foreach(QTcpSocket* socket, neuronReceivers_) {
		tcpServer_->publish(sendMe, socket);
	}
}

void ConnectionManager::newConnection(QTcpSocket* socket)
{
	neuronReceivers_.insert(socket);
}

void ConnectionManager::disconnected(QTcpSocket* socket)
{
	neuronReceivers_.remove(socket);
}

void ConnectionManager::dataArrived(QTcpSocket* socket, QVariant data)
{
	/* a socket can register itself for being notified about
	 * - sensor updates
	 * - world changes
	 *
	 * furthermore any connected socket is allowed to send neuron updates which
	 * will be forwarded to the according being.
	 */


	/* handle incoming actuator data */
	QString beingId;
	QString actuatorId;
	QList<qreal> actuatorNeurons;
	neuronSerializer_.deserializeActuator(data, &beingId, &actuatorId, &actuatorNeurons);

	emit actuatorUpdate(beingId, actuatorId, actuatorNeurons);
}
