#include "../api/LedTask.h"

LedTask::LedTask(int greenPin, 
                int redPin, 
                SharedState& state, 
                SemaphoreHandle_t& sharedStateMutex)
    : state(NOT_CONNECT), 
    greenLed(greenPin),
    redLed(redPin),
    sharedState(state), 
    sharedStateMutex(sharedStateMutex) {
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
            greenLed.turnOn();
            redLed.turnOff();
            break;

        case NOT_CONNECT:
            greenLed.turnOff();
            redLed.turnOn();
            break;
    }
}
