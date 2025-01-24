#include "Potentiometer.h"


Potentiometer::Potentiometer(int potPin){
    this->potPin = potPin;
}

int Potentiometer::getPos(){
    pos = analogRead(potPin);
    pos = map(pos, 0, 1023, 0, 90);
    return pos;
}

