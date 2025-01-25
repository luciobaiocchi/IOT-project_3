#ifndef __LCDTASK__
#define __LCDTASK__

#include "Arduino.h"
#include "Task.h"
#include "Properties.h"
#include "LiquidCrystal_I2C.h"
#include "Mode.h"


class LCDTask: public Task{
public:
    LCDTask(Properties& prop);  
    void init(int period);  
    void tick();
private:
    Properties& prop;
    void displayNewMode();
    void displayNewPos();
    LiquidCrystal_I2C* lcd;
    int currentPos;
    Mode currentMode;
};




#endif