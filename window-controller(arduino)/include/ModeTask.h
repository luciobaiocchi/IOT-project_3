#ifndef __MODETASK__
#define __MODETASK__

#include "Task.h"
#include "Button.h"
#include "TickCounter.h"
#include "Properties.h"


class ModeTask : public Task {
public:
    ModeTask(int buttonPin, Properties& prop);  
    void init(int period);  
    void tick();
private:
    Button* button;
    Properties& prop;
    TickCounter timer;
    void changeMode();
};

#endif
