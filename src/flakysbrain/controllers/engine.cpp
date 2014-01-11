#include "engine.h"

#include <QTimer>

#include "actionobjects/neuron.h"

#include <QDebug>

Engine::Engine(QObject *parent) :
    QThread(parent)
{
    ActionObjectPtr ao = addActionObject(ActionObjectPtr(new Neuron()));

    postMessage(timer_.getCurrentTime() + 1000,
                ao->id(),
                MessagePtr(new Message())
                );

    QTimer::singleShot(0, this, SLOT(handleQueue()));
}

ActionObjectPtr Engine::addActionObject(ActionObjectPtr ao)
{
    action_objects_by_id_[ao->id()] = ao;
    return ao;
}

void Engine::postMessage(Timestamp when, Id receiver, MessagePtr message)
{
    queue_[when] = QueueAction(receiver, message);
}

void Engine::handleQueue()
{
    if( !queue_.empty() ) {
        auto i = queue_.begin();
        Timestamp execution_time = i.key();

        auto wait_time = (execution_time - timer_.getCurrentTime())  / 1000000;
        if( wait_time > 0 ) {
            /* it's not our turn yet. wait a moment and start calling yourself again. */
            QTimer::singleShot(wait_time, this, SLOT(handleQueue()));
        } else {
            QueueAction turn_action = i.value();
            queue_.erase(i);

            ActionObjectPtr action_object = action_objects_by_id_[turn_action.first];
            MessagePtr message = turn_action.second;

            action_object->handleMessage(execution_time, message, this);

            QTimer::singleShot(0, this, SLOT(handleQueue()));
        }
    } else {
        QTimer::singleShot(1000, this, SLOT(handleQueue()));
    }

}
