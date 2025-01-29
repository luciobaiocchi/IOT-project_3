#ifndef __GATETASK__
#define __GATETASK__

#include <Arduino.h>
#include "Task.h"
#include "Button.h"
#include "TickCounter.h"
#include "Properties.h"
#include "Potentiometer.h"
#include "Gate.h"


class GateTask : public Task {
public:
    GateTask(Properties& prop, int servoPin);  
    void init(int period);  
    void tick();
private:
    Properties& prop;
    Potentiometer* pot;
    Gate* gate;
};

#endif
