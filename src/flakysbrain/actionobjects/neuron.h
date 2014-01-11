#ifndef NEURON_H
#define NEURON_H

#include "actionobject.h"

class Neuron : public ActionObject
{
public:
    Neuron();

protected:
    void handleMessage(Timestamp time, MessagePtr msg);
};

#endif // NEURON_H
