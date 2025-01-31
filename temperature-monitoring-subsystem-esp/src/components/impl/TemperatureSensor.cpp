#include "../api/TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(int pin) : sensorPin(pin) {
    pinMode(sensorPin, INPUT);
}

int TemperatureSensor::readTemperature() {
    int rawValue = analogRead(sensorPin);
    int voltage = rawValue * (3.3 / 4095.0);
    int temperature = (voltage - 0.5) * 100; 
    return temperature;
}
