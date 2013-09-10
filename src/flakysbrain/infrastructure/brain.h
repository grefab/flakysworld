#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>

class Brain : public QObject
{
    Q_OBJECT
public:
    explicit Brain(QObject *parent = 0);

};

#endif // BRAIN_H
