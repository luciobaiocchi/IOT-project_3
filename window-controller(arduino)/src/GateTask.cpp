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
        if (pot->getPos() != gate->getPos()){
            gate->move(pot->getPos());
        }
    }
}
