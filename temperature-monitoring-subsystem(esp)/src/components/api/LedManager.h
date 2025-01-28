#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <Arduino.h>

class LedManager {
public:
    LedManager(int pin);
    void turnOn();
    void turnOff();
    void blink(int delayMs);

private:
    int ledPin;
};

#endif
