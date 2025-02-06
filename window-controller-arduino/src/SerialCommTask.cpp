#include "SerialCommTask.h"

SerialCommTask::SerialCommTask(Properties& prop) : prop(prop) {
    MsgService.init();
    currentState = State::SEND;
}

void SerialCommTask::init(int period){
    Task::init(period);   
}

/*  Send Messaggi --> M000 --> livello apertura
                    A
                    
    Receive ---> M+00  --> temp
                 A000  --> livello apertura */
void SerialCommTask::tick(){
    switch (currentState){
        case State::SEND:
            send();
            break;
        case State::RECEIVE:
            receive();
            break;
    }
}

void SerialCommTask::receive(){
    if (MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg(); 
        currentState = State::SEND;

        if (msg->getContent().charAt(0) == 'N' && prop.getMode() == Mode::AUTOMATIC){
            prop.setPercPosition(msg->getContent().substring(1, 4).toInt());
        }else if (msg->getContent().charAt(0) == 'N' && prop.getMode() == Mode::MANUAL){
            int temp = msg->getContent().substring(2, 4).toInt();
            if (msg->getContent().charAt(1) == '-') {
                temp = -temp;
            }
            prop.setTemp(temp);
        }
        if (msg->getContent().charAt(0) == 'M' && prop.getMode() == Mode::AUTOMATIC){
            prop.setMode(Mode::MANUAL);
            int temp = msg->getContent().substring(2, 4).toInt();
            if (msg->getContent().charAt(1) == '-') {
                temp = -temp;
            }
            prop.setTemp(temp);
        }else if(msg->getContent().charAt(0) == 'A' && prop.getMode() == Mode::MANUAL) {
            prop.setMode(Mode::AUTOMATIC);
            prop.setPercPosition(msg->getContent().substring(1, 4).toInt());
        }
        delete msg;    
    }
    
}

void SerialCommTask::send(){
    currentState = State::RECEIVE;
    char buffer[5];
    if (prop.isChanged()){
        if (prop.getMode() == Mode::MANUAL) {
        snprintf(buffer, sizeof(buffer), "M%03d", prop.getPercPos()); 
        } else {
            strcpy(buffer, "A"); 
        }
    }else{
        if (prop.getMode() == Mode::MANUAL) {
        snprintf(buffer, sizeof(buffer), "N%03d", prop.getPercPos()); 
        } else {
            strcpy(buffer, "N"); 
        }
    }
    
    MsgService.sendMsg(buffer);
    receive();
}