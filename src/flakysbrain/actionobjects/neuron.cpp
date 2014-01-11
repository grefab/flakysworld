#include "neuron.h"

#include <QDebug>

Neuron::Neuron()
{
}

void Neuron::handleMessage(Timestamp time, MessagePtr msg)
{
    qDebug() << time;

    postMessage(time + 100 * MILLISECONDS, id(), MessagePtr(new Message()));
}
