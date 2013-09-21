#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QHostAddress address, quint16 port, QObject *parent = 0);
    ~Client();

public slots:
    void start();
    void stop();
    void send(QByteArray data);

protected slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);

private:
    void retry();

    QHostAddress address_;
    quint16 port_;
    QTcpSocket socket;

    bool wantConnection_;
    bool retrying_;

};

#endif // CLIENT_H
