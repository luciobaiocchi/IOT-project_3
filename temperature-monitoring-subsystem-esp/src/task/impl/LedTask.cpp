#include "../api/LedTask.h"

LedTask::LedTask(int greenPin, 
                int redPin, 
                SharedState& state, 
                SemaphoreHandle_t& sharedStateMutex)
    : state(NOT_CONNECT),
    greenPin(greenPin), 
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
        state = CONNECT;
    } else {
        state = NOT_CONNECT;
    }

    xSemaphoreGive(sharedStateMutex);

    switch (state) {
        case CONNECT:
            digitalWrite(greenPin, HIGH);
            digitalWrite(redPin, LOW);
            break;

        case NOT_CONNECT:
            digitalWrite(greenPin, LOW);
            digitalWrite(redPin, HIGH);
            break;
    }
}
