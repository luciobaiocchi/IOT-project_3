#include "TickCounter.h"

TickCounter::TickCounter(){
    tmpTime = 0;
}


void TickCounter::startTimer(int tick){
    tmpTime = tick;
}

bool TickCounter::isTimeElapsed(){
    return tmpTime <= 0;
}

void TickCounter::dec(){
    tmpTime--;  
}


