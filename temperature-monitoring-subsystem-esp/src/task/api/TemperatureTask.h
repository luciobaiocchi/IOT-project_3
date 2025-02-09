#ifndef TEMPERATURETASK_H
#define TEMPERATURETASK_H

#include "./data/api/SharedState.h"
#include "./config/config.h"
#include "./components/api/TemperatureSensor.h"

#include <Arduino.h>

class TemperatureTask {
public:
    TemperatureTask(int sensorPin, 
                    SharedState& state, 
                    SemaphoreHandle_t& sharedStateMutex);
    void update();

private:
    TaskState state;
    TemperatureSensor sensor;
    SharedState& sharedState;
    SemaphoreHandle_t& sharedStateMutex;
};

#endif
