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
    bool isModeChanged();
    int getNewPos();
    char getCharMode();

private:
    Mode modality;
    int position;
    bool modeChanged;
    int newPos;
};






#endif