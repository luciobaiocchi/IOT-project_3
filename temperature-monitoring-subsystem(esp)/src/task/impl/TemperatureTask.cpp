#include "../api/TemperatureTask.h"

TemperatureTask::TemperatureTask(int sensorPin, SharedState& state)
    : sensorPin(sensorPin), sharedState(state) {
    pinMode(sensorPin, INPUT);
}

void TemperatureTask::update() {
    unsigned long currentTime = millis();
    if (currentTime - sharedState.getLastReadTime() >= sharedState.getReadFrequency()) {
        int rawValue = analogRead(sensorPin);
        float voltage = rawValue * (3.3 / 4095.0);
        sharedState.setTemperature((voltage - 0.5) * 100);

        sharedState.setLastReadTime(currentTime);
    }
}
