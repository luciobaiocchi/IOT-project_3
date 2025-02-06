#ifndef __SERIALCOMMUNICATION__
#define __SERIALCOMMUNICATION__

#include "Task.h"
#include "MsgService.h"
#include "Gate.h"
#include "Properties.h"
#include "Mode.h"


class SerialCommTask : public Task {

public:
  SerialCommTask(Properties& prop);  
  void init(int period);  
  void tick();
  void receive();
  void send();
  enum State{
    SEND,
    RECEIVE
  };
private:
  Properties& prop;
  State currentState;
};


#endif