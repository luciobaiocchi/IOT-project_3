#ifndef TEMPERATURETASK_H
#define TEMPERATURETASK_H

#include "./data/api/SharedState.h"

#include <Arduino.h>

class TemperatureTask {
public:
    TemperatureTask(int sensorPin, SharedState& state);
    void update();

private:
    int sensorPin;
    SharedState& sharedState;
};

#endif
