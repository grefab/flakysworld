#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>
#include <QHash>
#include <QMap>
#include <QPair>

#include "actionobjects/actionobject.h"
#include "helpers/message.h"
#include "helpers/timer.h"

class Engine : public QThread
{
    Q_OBJECT

public:
    explicit Engine(QObject *parent = 0);

public slots:
    ActionObjectPtr addActionObject(ActionObjectPtr ao);
    void postMessage(Timestamp when, Id receiver, MessagePtr message);

protected slots:
    void handleQueue();

private:
    typedef QHash<Id, ActionObjectPtr> ActionObjectsById;
    ActionObjectsById action_objects_by_id_;

    Timer timer_;

    typedef QPair<Id, MessagePtr> QueueAction;
    typedef QMap<Timestamp, QueueAction> ActionObjectQueue;
    ActionObjectQueue queue_;

private slots:

};

#endif // ENGINE_H
