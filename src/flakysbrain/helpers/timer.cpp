#include "timer.h"

Timer::Timer()
{
    elapsed_timer_.start();
}

Timestamp Timer::getCurrentTime()
{
    return elapsed_timer_.nsecsElapsed();
}

