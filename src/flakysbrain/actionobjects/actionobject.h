#ifndef ACTIONOBJECT_H
#define ACTIONOBJECT_H

#include <QSharedPointer>
#include <helpers/id.h>
#include <helpers/timer.h>
#include <helpers/message.h>

class Engine;

class ActionObject;
typedef QSharedPointer<ActionObject> ActionObjectPtr;

class ActionObject
{
public:
    explicit ActionObject();
    virtual ~ActionObject();

    Id id() const { return id_; }

    void handleMessage(Timestamp time, MessagePtr msg, Engine *engine);

protected:
    virtual void handleMessage(Timestamp time, MessagePtr msg) = 0;
    void postMessage(Timestamp when, Id receiver, MessagePtr message);

private:
    const Id id_;
    Engine* engine_;

};

#endif // ACTIONOBJECT_H
