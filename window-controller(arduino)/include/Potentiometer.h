#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include <Arduino.h>


class Potentiometer {
public:
    Potentiometer(int potPin);
    virtual int getPos();
private:
    int potPin;
    int pos;
};


#endif