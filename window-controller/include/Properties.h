#ifndef __PROPERTIES__
#define __PROPERTIES__

#include "Mode.h"


class Properties {
public:
    Properties();
    Mode getMode();
    int getPos();
    void setMode(Mode modality);
    void setMode(char newmod);
    void setPosition(int position);
    char getCharMode();
    int getTemp();
    void setTemp(int temp);
private:
    Mode modality;
    int position;
    int temp;

};






#endif