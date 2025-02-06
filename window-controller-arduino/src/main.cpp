#include <Arduino.h>
#include "Scheduler.h"
#include "Properties.h"
#include "ModeTask.h"
#include "GateTask.h"
#include "SerialCommTask.h"
#include "LCDTask.h"

Scheduler scheduler;


void setup() {
  scheduler.init(50);
  Properties prop = Properties();

  Serial.begin(9600);


  Task* modeTask = new ModeTask(13, prop);
  modeTask->init(100);

  Task* gateTask = new GateTask(prop, 5);
  gateTask->init(100);


  Task* serialComm = new SerialCommTask(prop);
  serialComm->init(100);

  Task* lcdTask = new LCDTask(prop);
  lcdTask->init(150);


  
  scheduler.addTask(gateTask);
  scheduler.addTask(modeTask);
  scheduler.addTask(lcdTask);
  scheduler.addTask(serialComm);
}

void loop() {
  scheduler.schedule();
}

