#include "GateTask.h"

GateTask::GateTask(Properties &prop, int servoPin): prop(prop) {
    pot = new Potentiometer(A5);
    gate = new Gate(servoPin);
}

void GateTask::init(int period) {
    Task::init(period);
}

void GateTask::tick() {
    if (prop.getMode() == Mode::MANUAL){
        gate->checkServo();
        Serial.println(pot->getPos());
        Serial.println(gate->getPos());
        if (pot->getPos() >= gate->getPos()+3 || pot->getPos() <= gate->getPos()-3 ){
            gate->move(pot->getPos());
        }
    }
}
