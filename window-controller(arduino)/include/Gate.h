#ifndef __GATE__
#define __GATE__

#include <Arduino.h>
#include <Servo.h>
#include "TickCounter.h"

class Gate {
public:
    Gate(int pinServo); 
    void checkServo();
    void move(int pos);
    int getPos();
private:
    Servo servo;
    int servoPin;
    TickCounter timer;
    int detachCounter;
    int currentPos;
};

#endif