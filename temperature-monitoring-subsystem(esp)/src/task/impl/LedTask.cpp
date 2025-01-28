#include "../api/LedTask.h"

LedTask::LedTask(int greenPin, int redPin, SharedState& state)
    : greenPin(greenPin), redPin(redPin), sharedState(state) {
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
}

void LedTask::update() {
    if (sharedState.isMqttNetworkConnected()) {
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, LOW);
    } else {
        digitalWrite(greenPin, LOW);
        digitalWrite(redPin, HIGH);
    }
}
