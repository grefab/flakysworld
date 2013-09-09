#include "tcpclient.h"
#include <QHostAddress>

#include <QDebug>

TcpClient::TcpClient(QObject* parent) :
    QObject(parent)
{
    connect(&socket_, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(&socket_, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(&socket_, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(&socket_, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
    connect(&socket_, SIGNAL(readyRead()), this, SLOT(dataAvailable()));

    qDebug() << "created";
}

TcpClient::~TcpClient()
{
    socket_.close();
}

void TcpClient::start(QString host, int port)
{
    qDebug() << "connecting...";
    socket_.connectToHost(host, port);
}

void TcpClient::onConnect()
{
    qDebug() << "connected.";
}

void TcpClient::onDisconnect()
{
    qDebug() << "disconnected.";
}

void TcpClient::sendLine(const QVariant& data)
{
    /* perform serialization */
    QByteArray binaryData = variantBinaryConverter_.toByteArray(data);

    /* tell socket! newline tells that data is finished. */
    binaryData.append("\n");
    /*qDebug() << "write" <<*/ socket_.write(binaryData);
}

void TcpClient::dataAvailable()
{
    /* if we have a complete line, pass it on! */
    while ( socket_.canReadLine() ) {
        QByteArray line = socket_.readLine().trimmed();

        QVariant parsedData = variantBinaryConverter_.toVariant(line);

        emit dataArrived(parsedData.toMap());
    }

}
