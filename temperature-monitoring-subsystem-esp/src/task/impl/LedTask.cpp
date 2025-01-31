#include "../api/LedTask.h"

LedTask::LedTask(int greenPin, 
                int redPin, 
                SharedState& state, 
                SemaphoreHandle_t& sharedStateMutex)
    : greenPin(greenPin), 
    redPin(redPin), 
    sharedState(state), 
    sharedStateMutex(sharedStateMutex) {
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
}

void LedTask::update() {
    while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    if (sharedState.isMqttNetworkConnected() && sharedState.isWifiNetworkConnected()) {
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, LOW);
    } else {
        digitalWrite(greenPin, LOW);
        digitalWrite(redPin, HIGH);
    }

    xSemaphoreGive(sharedStateMutex);
}
