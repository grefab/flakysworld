#include "universeserver.h"
#include "constants.h"

UniverseServer::UniverseServer(Universe* universe, QObject *parent) :
    QThread(parent),
    universe_(universe)
{
    moveToThread(this);

    start();
}

UniverseServer::~UniverseServer()
{
    /* do not process further events. */
    quit();

    /* wait for our processing to be finished. */
    wait();
}

void UniverseServer::run()
{
    /* we need a tcp connection to the outside world */
    tcpServer_ = new TcpServer(2345, this);

    /* get notified of anything the tcp server wants to tell us */
    connect(tcpServer_, SIGNAL(newConnection(QTcpSocket*)), this, SLOT(newConnection(QTcpSocket*)));
    connect(tcpServer_, SIGNAL(disconnected(QTcpSocket*)), this, SLOT(disconnected(QTcpSocket*)));
    connect(tcpServer_, SIGNAL(dataArrived(QTcpSocket*,QVariantMap)), this, SLOT(dataArrived(QTcpSocket*,QVariantMap)));

    /* notify universe if we have new actuator data */
    connect(this, SIGNAL(actuatorUpdate(QString,QString,QList<qreal>)), universe_, SLOT(actuatorRefresh(QString,QString,QList<qreal>)));

    /* get notified by universe if sensor or thing updates */
    connect(universe_, SIGNAL(sensorDataAvaliable(QString,QString,QList<qreal>)), this, SLOT(sensorUpdate(QString,QString,QList<qreal>)));
    connect(universe_->world(), SIGNAL(thingUpdate(QString,QPointF,qreal)), this, SLOT(thingUpdate(QString,QPointF,qreal)));

    QThread::run();
}

void UniverseServer::sensorUpdate(QString beingId, QString sensorId, QList<qreal> sensorNeurons)
{
    if ( sensorReceivers_.empty() )
        return;

    sendSensorUpdate(beingId, sensorId, sensorNeurons);
}

void UniverseServer::thingUpdate(QString thingId, QPointF position, qreal rotation)
{
    if ( worldReceivers_.empty() )
        return;

    sendThingUpdate(thingId, position, rotation);
}

void UniverseServer::newConnection(QTcpSocket* socket)
{
    Q_UNUSED(socket)

    qDebug() << "socket" << socket->localAddress() << "connected.";
}

void UniverseServer::disconnected(QTcpSocket* socket)
{
    sensorReceivers_.remove(socket);
    actuatorReceivers_.remove(socket);
    worldReceivers_.remove(socket);

    qDebug() << "disconnected: socket" << socket->localAddress();
}

void UniverseServer::dataArrived(QTcpSocket* socket, QVariantMap data)
{
    /* a socket can register itself for being notified about
     * - sensor updates
     * - world changes
     *
     * furthermore any connected socket is allowed to send neuron updates which
     * will be forwarded to the according being.
     */
    const QString type = data[KEY_TYPE].toString();

    /* we have received an actuator */
    if(type == TYPE_ACTUATORINPUT) {
        handleActuatorinput(data);
        return;
    }

    /* we have received someone who wants to register */
    if(type == TYPE_REGISTER) {
        handleRegister(data, socket);
        return;
    }

    /* we have received someone who wants to unregister */
    if(type == TYPE_UNREGISTER) {
        handleUnregister(data, socket);
        return;
    }
}

void UniverseServer::handleActuatorinput(const QVariantMap& data)
{
    /* decode incoming actuator data */
    QString beingId;
    QMap<QString, QList<qreal> > actuators;
    entitySerializer_.deserializeActuators(data, &beingId, &actuators);

    /* tell universe */
    foreach( QString actuatorId, actuators.keys() ) {
        const QList<qreal> actuatorNeurons = actuators.value(actuatorId);
        emit actuatorUpdate(beingId, actuatorId, actuatorNeurons);

        /* tell registered clients */
        if ( !actuatorReceivers_.empty() ) {
            sendActuatorUpdate(beingId, actuatorId, actuatorNeurons);
        }
    }
}

void UniverseServer::handleRegister(const QVariantMap& data, QTcpSocket* socket)
{
    const QString concerns = data[KEY_CONCERNS].toString();

    if(concerns == CONCERNS_SENSORS) {
        sensorReceivers_.insert(socket);
        return;
    }

    if(concerns == CONCERNS_ACTUATORS) {
        actuatorReceivers_.insert(socket);
        return;
    }

    if(concerns == CONCERNS_WORLD) {
        /* send complete world initally as "keyframe" */
        sendCompleteWorld(socket);
        worldReceivers_.insert(socket);
        return;
    }
}

void UniverseServer::handleUnregister(const QVariantMap& data, QTcpSocket* socket)
{
    const QString concerns = data[KEY_CONCERNS].toString();

    if(concerns == CONCERNS_SENSORS) {
        sensorReceivers_.remove(socket);
        return;
    }

    if(concerns == CONCERNS_SENSORS) {
        actuatorReceivers_.remove(socket);
        return;
    }

    if(concerns == CONCERNS_WORLD) {
        worldReceivers_.remove(socket);
        return;
    }
}

void UniverseServer::sendSensorUpdate(const QString& beingId, const QString& sensorId, const QList<qreal>& sensorNeurons)
{
    /* get a variant to be sent */
    QVariantMap sendMe = entitySerializer_.serializeSensor(beingId, sensorId, sensorNeurons);

    /* define type */
    sendMe.insert(KEY_TYPE, TYPE_SENSOROUTPUT);

    /* tell all interested sockets about our sensor */
    foreach(QTcpSocket* socket, sensorReceivers_) {
        tcpServer_->send(sendMe, socket);
    }
}

void UniverseServer::sendActuatorUpdate(const QString& beingId, const QString& actuatorId, const QList<qreal>& actuatorNeurons)
{
    /* get a variant to be sent */
    QVariantMap sendMe = entitySerializer_.serializeActuator(beingId, actuatorId, actuatorNeurons);

    /* define type */
    sendMe.insert(KEY_TYPE, TYPE_ACTUATOROUTPUT);

    /* tell all interested sockets about our sensor */
    foreach(QTcpSocket* socket, actuatorReceivers_) {
        tcpServer_->send(sendMe, socket);
    }
}

void UniverseServer::sendThingUpdate(const QString& thingId, const QPointF& position, qreal rotation)
{
    /* get a variant to be sent */
    QVariantMap sendMe = entitySerializer_.serializeThing(thingId, QPolygonF(), position, rotation);

    /* define type */
    sendMe.insert(KEY_TYPE, TYPE_THING);

    /* tell all interested sockets about our updated thing */
    foreach(QTcpSocket* socket, worldReceivers_) {
        tcpServer_->send(sendMe, socket);
    }
}

void UniverseServer::sendCompleteWorld(QTcpSocket* socket)
{
    QList<Thing::Model> things = universe_->world()->getThingModels();

    foreach(const Thing::Model& thing, things) {
        /* get a variant to be sent */
        QVariantMap sendMe = entitySerializer_.serializeThing(thing.id_, thing.shape_, thing.position_, thing.rotation_);

        /* define type */
        sendMe.insert(KEY_TYPE, TYPE_THING);

        /* send the data to socket */
        tcpServer_->send(sendMe, socket);
    }
}
