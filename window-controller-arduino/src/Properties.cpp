#include "Properties.h"

Properties::Properties(){
    modality = Mode::AUTOMATIC;
    position = 0;
    temp = 50;
    isChangedVar = false;
}

Mode Properties::getMode(){
    return modality;
}

int Properties::getPos(){
    return position;
}

void Properties::setMode(Mode modality){
    isChangedVar = true;
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

void Properties::setPercPosition(int position){
    this->position = map(position, 0, 100, 0, 90);
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

int Properties::getPercPos(){
    return map(position, 0, 90, 0, 100);
}

bool Properties::isChanged(){
    if (isChangedVar == true){
        isChangedVar = false;
        return true;
    }
    return false;
}
