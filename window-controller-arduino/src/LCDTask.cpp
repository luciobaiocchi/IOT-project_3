#include "LCDTask.h"

LCDTask::LCDTask(Properties &prop): prop(prop){
    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->init();
    lcd->backlight();
    lcd->clear();
    displayNewMode();
    currentMode = Mode::MANUAL;
    currentPos = 1;
    currentTemp = 60;
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
    if (prop.getTemp() != currentTemp || prop.getPos() != currentPos) {
        currentTemp = prop.getTemp();
        currentPos = prop.getPos();
        displayNewParam();
    }

}

void LCDTask::displayNewMode() {
    String message = "";
    lcd->clear();
    lcd->home();

    if (currentMode == Mode::MANUAL){
        lcd->print("MANUAL");
    }else {
        lcd->print("AUTOMATIC");
    }
    displayNewParam();
    lcd->print(message);
    
}

void LCDTask::displayNewParam() {
    lcd->setCursor(0, 1);
    if (currentMode == Mode::MANUAL){
        lcd->print("Pos: " + (String)currentPos + "    T: " + (String)currentTemp + " ");
    }else{
        lcd->print("Pos: " + (String)currentPos);
    }
    
}


