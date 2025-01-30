#ifndef __PROPERTIES__
#define __PROPERTIES__

#include <Arduino.h>
#include "Mode.h"


class Properties {
public:
    Properties();
    Mode getMode();
    int getPos();
    void setMode(Mode modality);
    void setMode(char newmod);
    void setPosition(int position);
    void setPercPosition(int position);
    char getCharMode();
    int getTemp();
    void setTemp(int newTemp);
    int getPercPos();
private:
    Mode modality;
    int position;
    int temp;

};






#endif