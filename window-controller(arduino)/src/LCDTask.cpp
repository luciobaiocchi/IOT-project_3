#include "LCDTask.h"

LCDTask::LCDTask(Properties &prop): prop(prop){
    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->init();
    lcd->backlight();
    displayNewMode();
    currentMode = Mode::AUTOMATIC;
    currentPos = -1;
}

void LCDTask::init(int period){
    Task::init(period);
}

/* Temp control to be implemented.*/
void LCDTask::tick() {
    if (currentMode != prop.getMode()) {
        currentMode = prop.getMode();
        displayNewMode();
    }
    if (currentPos != prop.getPos()) {
        currentPos = prop.getPos();
        displayNewPos();
    }

}

void LCDTask::displayNewMode() {
    String message;
    lcd->clear();
    lcd->home();

    if (currentMode == Mode::MANUAL){
        lcd->print("MANUAL");
    }else {
        lcd->print("AUTOMATIC");
        message = "       T:23";
    }
    lcd->setCursor(0, 1);
    lcd->print(message);
}

void LCDTask::displayNewPos() {
    lcd->setCursor(0, 1);
    lcd->print("Pos:" + (String)currentPos);
}



