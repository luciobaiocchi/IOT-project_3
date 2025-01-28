#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h> 

class TemperatureSensor {
public:
    TemperatureSensor(int pin);
    float readTemperature();

private:
    int sensorPin;
};

#endif 
