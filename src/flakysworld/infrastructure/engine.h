#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>
#include "world.h"

class Engine : public QThread
{
    Q_OBJECT

public:
    Engine(World* world, QObject *parent = 0);
    ~Engine();

    void start();

signals:
    void updatedFPS(int fps);

protected:
    void run();

    World* world_;

private slots:
    /* used internally by our timers */
    void simulationStep();
    void printFPS();

private:
    unsigned long stepsPerformed_;
};

#endif // ENGINE_H
