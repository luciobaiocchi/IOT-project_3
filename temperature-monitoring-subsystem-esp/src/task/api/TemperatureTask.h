#ifndef TEMPERATURETASK_H
#define TEMPERATURETASK_H

#include "./data/api/SharedState.h"
#include "./config/config.h"
#include "./components/api/TemperatureSensor.h"

#include <Arduino.h>
#include <DHT.h>  // Include la libreria DHT

#define DHTTYPE DHT11  // Specifica il tipo di sensore (DHT11)

class TemperatureTask {
public:
    TemperatureTask(int dhtPin, 
                    SharedState& state, 
                    SemaphoreHandle_t& sharedStateMutex);
    void update();

private:
    TaskState state;
    int dhtPin;
    DHT dht;  // Oggetto DHT
    SharedState& sharedState;
    SemaphoreHandle_t& sharedStateMutex;
};

#endif
