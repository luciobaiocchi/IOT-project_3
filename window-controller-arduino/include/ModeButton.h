#ifndef __MODEBUTTON__
#define __MODEBUTTON__

#include "Button.h"


class ModeButton: public Button {

public: 
  ModeButton(int pin);
  bool isPressed();
private:
  int pin;
};

#endif
