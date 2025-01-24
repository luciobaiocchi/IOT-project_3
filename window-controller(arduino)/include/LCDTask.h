#ifndef __LCDTASK__
#define __LCDTASK__

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
    void display();
    LiquidCrystal_I2C* lcd;
    int currentPos;
    Mode currentMode;
};




#endif