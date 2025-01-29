#include "../api/TemperatureTask.h"

TemperatureTask::TemperatureTask(int sensorPin, SharedState& state)
    : sensorPin(sensorPin), sharedState(state) {
    pinMode(sensorPin, INPUT);
}

void TemperatureTask::update() {
    unsigned long currentTime = millis();
    if (currentTime - sharedState.getLastReadTime() >= sharedState.getFrequency()) {
        int rawValue = analogRead(sensorPin);
        
        float temperature = map(rawValue, 0, 4095, -30.0, 50.0);
        
        sharedState.setTemperature(temperature);
        sharedState.setLastReadTime(currentTime);

        Serial.println(sharedState.getTemperature());
    }
}
