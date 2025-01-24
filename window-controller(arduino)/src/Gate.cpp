#include "Gate.h"

#define DETACH_TICK 3

Gate::Gate(int servoPin) { 
    this->servoPin = servoPin;
    servo.attach(servoPin);
    servo.write(0);
    timer = TickCounter();
    detachCounter = DETACH_TICK;
}

void Gate::checkServo(){
    detachCounter--;
    if (detachCounter <= 0){
        servo.detach();
    }
}

int Gate::getPos(){
    return currentPos;
}

void Gate::move(int pos){
    servo.attach(servoPin);
    detachCounter = DETACH_TICK;
    servo.write(pos);
}