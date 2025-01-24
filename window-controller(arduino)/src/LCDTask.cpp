#include "LCDTask.h"

LCDTask::LCDTask(Properties &prop): prop(prop){
    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->init();
    lcd->backlight();
    displayManual();
}

void LCDTask::init(int period){
    Task::init(period);
}

/* Temp control to be implemented.*/
void LCDTask::tick() {
    if (currentPos != prop.getPos() || currentMode != prop.getMode()) {
        currentMode = prop.getMode();
        currentPos = prop.getPos();
        display();
    }
}

void LCDTask::display(){
    String message;
    lcd->clear();
    lcd->home();
    if (currentMode == Mode::MANUAL){
        lcd->print("MANUAL");
        message = "Pos:" + (String)currentPos;
    }else {
        lcd->print("AUTOMATIC");
        message = "Pos:" + (String)currentPos + "T:23";
    }
    lcd->setCursor(1, 0);
    lcd->print(message);
}

