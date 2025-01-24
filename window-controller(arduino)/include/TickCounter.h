#ifndef __TICKCOUNTER__
#define __TICKCOUNTER__

#include "Arduino.h"


class TickCounter {
public:
    TickCounter();
    void startTimer(int time);
    bool isTimeElapsed();
    void dec();
private:
    int tmpTime;
    int tick;
};

#endif
