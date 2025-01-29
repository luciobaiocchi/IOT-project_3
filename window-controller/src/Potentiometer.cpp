#include "Potentiometer.h"


Potentiometer::Potentiometer(int potPin){
    this->potPin = potPin;
}

int Potentiometer::getPos(){
    pos = analogRead(potPin);
    //Serial.println(pos);
    pos = map(pos, 0, 1023, 0, 90);
    //Serial.println(pos);
    return pos;
}

