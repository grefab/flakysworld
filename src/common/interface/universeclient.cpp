#include "universeclient.h"
#include "constants.h"

UniverseClient::UniverseClient(QObject* parent) :
    QThread(parent)
{
    /* make sure initateConnection cannot be called yet */
    locker_.lock();

    qRegisterMetaType< Thing::Model >("Thing::Model");

    moveToThread(this);

    start();
}

UniverseClient::~UniverseClient()
{
    /* do not process further events. */
    quit();

    /* wait for our processing to be finished. */
    wait();
}

void UniverseClient::run()
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


void UniverseClient::initiateConnection()
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

void UniverseClient::connected()
{
    registerForWorld();
    registerForSensors();
    registerForActuators();
    pushFlaky();
}

void UniverseClient::disconnected()
{

}

void UniverseClient::dataArrived(QVariantMap data)
{
    if( data.value(KEY_TYPE).toString() == TYPE_THING ) {
        Thing::Model thingModel;
        entitySerializer_.deserializeThing(data, &thingModel.id_, &thingModel.shape_, &thingModel.position_, &thingModel.rotation_);

        emit thingUpdated(thingModel);
    }

    if( data.value(KEY_TYPE).toString() == TYPE_SENSOROUTPUT ) {
        QString sensorBeingId;
        QString sensorId;
        QList<qreal> sensorNeurons;
        entitySerializer_.deserializeSensor(data, &sensorBeingId, &sensorId, &sensorNeurons);

        if( sensorBeingId == "flaky" && sensorId == "eye" ) {
            emit eyeUpdated(sensorNeurons);
        }
    }

    if( data.value(KEY_TYPE).toString() == TYPE_ACTUATOROUTPUT ) {
        QString actuatorBeingId;
        QString actuatorId;
        QList<qreal> actuatorNeurons;
        entitySerializer_.deserializeActuator(data, &actuatorBeingId, &actuatorId, &actuatorNeurons);

        if( actuatorBeingId == "flaky" ) {
            emit actuatorUpdated(actuatorId, actuatorNeurons);
        }
    }
}

void UniverseClient::registerForWorld()
{
    /* register on flakysworld server */
    QVariantMap map;
    map.insert(KEY_TYPE, TYPE_REGISTER)	;
    map.insert(KEY_CONCERNS, CONCERNS_WORLD);

    tcpClient_->sendLine(map);
}

void UniverseClient::registerForSensors()
{
    /* register on flakysworld server */
    QVariantMap map;
    map.insert(KEY_TYPE, TYPE_REGISTER)	;
    map.insert(KEY_CONCERNS, CONCERNS_SENSORS);

    tcpClient_->sendLine(map);
}

void UniverseClient::registerForActuators()
{
    /* register on flakysworld server */
    QVariantMap map;
    map.insert(KEY_TYPE, TYPE_REGISTER)	;
    map.insert(KEY_CONCERNS, CONCERNS_ACTUATORS);

    tcpClient_->sendLine(map);
}

void UniverseClient::actuatorUpdate(QString actuatorId, QList<qreal> actuatorNeurons)
{
    /* prepare and send an actuator singal */
    QVariantMap map;
    QVariantMap actuators;
    QVariantList actuatorNeuronList;
    foreach( qreal actuatorNeuron, actuatorNeurons ) { actuatorNeuronList.append(actuatorNeuron); }
    actuators.insert(actuatorId, actuatorNeuronList);
    map.insert(KEY_TYPE, TYPE_ACTUATORINPUT);
    map.insert(KEY_BEING, "flaky");
    map.insert(KEY_BEINGS_ACTUATORS, actuators);

    tcpClient_->sendLine(map);
}

void UniverseClient::pushFlaky()
{
    /* push flaky a bit, so we see action! */
    QList<qreal> neurons;
    neurons.append(0.3);
    actuatorUpdate("thrl", neurons);
}
