#include "ModeButton.h"
#include "Arduino.h"


ModeButton::ModeButton(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);     
} 
  
bool ModeButton::isPressed(){
    return digitalRead(pin) == HIGH;
}

