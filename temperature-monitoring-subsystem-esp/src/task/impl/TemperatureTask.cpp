#include "../api/TemperatureTask.h"

TemperatureTask::TemperatureTask(int sensorPin, 
                                SharedState& state, 
                                SemaphoreHandle_t& sharedStateMutex)
    : state(NOT_CONNECT),
    sensorPin(sensorPin), 
    sharedState(state),
    sharedStateMutex(sharedStateMutex) {
    pinMode(sensorPin, INPUT);
}

void TemperatureTask::update() {
    unsigned long currentTime = millis();

    while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    if (sharedState.isMqttNetworkConnected() == true){
        state = CONNECT;
    } else {
        state = NOT_CONNECT;
    }

    xSemaphoreGive(sharedStateMutex);

    switch (state)
    {
    case CONNECT:
        while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
            vTaskDelay(pdMS_TO_TICKS(100));
        }

        if (currentTime - sharedState.getLastReadTime() >= sharedState.getFrequency()) {
            int rawValue = analogRead(sensorPin);
            int temperature = map(rawValue, 0, 4095, -30, 50);

            sharedState.setTemperature(temperature);
            sharedState.setLastReadTime(currentTime);
        }

        xSemaphoreGive(sharedStateMutex);
        break;
    
    default:
        break;
    }
}
