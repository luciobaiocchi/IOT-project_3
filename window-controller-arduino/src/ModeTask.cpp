#include "ModeTask.h"
#include "ModeButton.h"


ModeTask::ModeTask(int buttonPin, Properties& prop): prop(prop){
    button = new ModeButton(buttonPin);
    timer = TickCounter();
}

void ModeTask::init(int period){
    Task::init(period);
}

void ModeTask::tick(){
    timer.dec();
    if (button->isPressed() && timer.isTimeElapsed()){
        changeMode();
        timer.startTimer(10);
    }
    
}

void ModeTask::changeMode(){
    if (prop.getMode() == Mode::MANUAL) {
        prop.setMode(Mode::AUTOMATIC);
    } else {
        prop.setMode(Mode::MANUAL);
    }
    
}
