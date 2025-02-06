#include "../api/TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(int pin) : sensorPin(pin) {
    pinMode(sensorPin, INPUT);
}

int TemperatureSensor::readTemperature() {
    int rawValue = analogRead(sensorPin);
    int temperature = map(rawValue, 0, 4095, -30, 50);
    return temperature;
}
