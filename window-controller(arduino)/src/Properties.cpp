#include "Properties.h"

Properties::Properties(){
    modality = Mode::MANUAL;
    position = 0;
    position = 0; 
    modeChanged = false; 
    newPos = 0; 
}

Mode Properties::getMode(){
    return modality;
}

int Properties::getPos(){
    return position;
}

void Properties::setMode(Mode modality){
    this->modality = modality;
}

void Properties::setMode(char newmod){
    if (newmod == 'M'){
        this->modality = Mode::MANUAL;
    }else{
        this->modality = Mode::AUTOMATIC;
    }
    modeChanged = true; 
}

void Properties::setPosition(int position){
    this->position = position;
}

bool Properties::isModeChanged(){
    return modeChanged;
}

int Properties::getNewPos(){
    return newPos;
}

char Properties::getCharMode(){
    if (modality == Mode::MANUAL){
        return 'M';
    }
    return 'A';
}
