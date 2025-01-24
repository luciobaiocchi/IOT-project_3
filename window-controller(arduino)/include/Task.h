#ifndef __TASK__
#define __TASK__

class Task {
  int myPeriod;
  int timeOpenElapsed;
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeOpenElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeOpenElapsed += basePeriod;
    if (timeOpenElapsed >= myPeriod){
      timeOpenElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }
  
};

#endif

