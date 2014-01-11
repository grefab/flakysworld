#ifndef TIMER_H
#define TIMER_H

#include <QElapsedTimer>

#define NANOSECONDS 1
#define MICROSECONDS 1000 * NANOSECONDS
#define MILLISECONDS 1000 * MICROSECONDS
#define SECONDS 1000 * MILLISECONDS

typedef qint64 Timestamp;

class Timer
{
public:
    Timer();
    Timestamp getCurrentTime();
private:
    QElapsedTimer elapsed_timer_;
};


#endif // TIMER_H
