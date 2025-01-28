#include "../api/LedManager.h"

LedManager::LedManager(int pin) : ledPin(pin) {
    pinMode(ledPin, OUTPUT);
}

void LedManager::turnOn() {
    digitalWrite(ledPin, HIGH);
}

void LedManager::turnOff() {
    digitalWrite(ledPin, LOW);
}

void LedManager::blink(int delayMs) {
    turnOn();
    delay(delayMs);
    turnOff();
    delay(delayMs);
}
