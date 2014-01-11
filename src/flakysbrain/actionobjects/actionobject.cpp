#include "actionobject.h"

#include "controllers/engine.h"

ActionObject::ActionObject() :
    id_(createId())
{
}

ActionObject::~ActionObject()
{
}

void ActionObject::handleMessage(Timestamp time, MessagePtr msg, Engine* engine)
{
    engine_ = engine;
    handleMessage(time, msg);
}

void ActionObject::postMessage(Timestamp when, Id receiver, MessagePtr message)
{
    engine_->postMessage(when, receiver, message);
}
