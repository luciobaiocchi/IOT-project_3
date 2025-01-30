#include "Properties.h"

Properties::Properties(){
    modality = Mode::AUTOMATIC;
    position = 0;
    temp = 50;
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
}

void Properties::setPosition(int position){
    this->position = position;
}



char Properties::getCharMode(){
    if (modality == Mode::MANUAL){
        return 'M';
    }
    return 'A';
}

int Properties::getTemp(){
    return temp;
}

void Properties::setTemp(int newTemp){
    this->temp = newTemp;
}
