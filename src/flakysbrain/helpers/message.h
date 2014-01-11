#ifndef MESSAGE_H
#define MESSAGE_H

#include <QSharedPointer>

class Message
{
public:
    Message();
};

typedef QSharedPointer<Message> MessagePtr;

#endif // MESSAGE_H
