#ifndef LEDTASK_H
#define LEDTASK_H

#include "./data/api/SharedState.h"

#include <Arduino.h>

class LedTask {
public:
    LedTask(int greenPin, int redPin, SharedState& state);
    void update();

private:
    int greenPin, redPin;
    SharedState& sharedState;
};

#endif
