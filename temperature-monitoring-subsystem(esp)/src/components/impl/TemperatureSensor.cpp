#include "../api/TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(int pin) : sensorPin(pin) {
    pinMode(sensorPin, INPUT);
}

float TemperatureSensor::readTemperature() {
    int rawValue = analogRead(sensorPin); // Lettura grezza dal sensore
    float voltage = rawValue * (3.3 / 4095.0); // Conversione a tensione (esempio per ESP32)
    float temperature = (voltage - 0.5) * 100; // Conversione in gradi Celsius
    return temperature;
}
