#include <Arduino.h>
#include "Scheduler.h"
#include "Properties.h"
#include "ModeTask.h"
#include "GateTask.h"
#include "SerialCommTask.h"

Scheduler scheduler;


void setup() {
  scheduler.init(50);
  Properties prop = Properties();


  //Task* modeTask = new ModeTask(1, prop);
  //modeTask->init(100);

  Task* gateTask = new GateTask(prop, 5);
  gateTask->init(100);

  //Task* serialComm = new SerialCommTask(prop);
  //serialComm->init(200);

 // scheduler.addTask(modeTask);
  scheduler.addTask(gateTask);
}

void loop() {
  scheduler.schedule();
}

