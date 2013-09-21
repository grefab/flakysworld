#include "brain.h"
#include <QDebug>


Brain::Brain(QObject *parent) :
    QObject(parent)
{
}

void Brain::sensorUpdate(QString sensorId, QList<qreal> sensorNeurons)
{
    if( sensorId == "eye" ) {
        qDebug() << "eye input received!";
    }
    qDebug() << sensorNeurons;
}
