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

        if (msg->getContent().charAt(0) == 'M'){
            prop.setMode(Mode::MANUAL);
            int temp = msg->getContent().substring(2, 4).toInt();
            if (msg->getContent().charAt(1) == '-') {
                temp = -temp;
            }
            prop.setTemp(temp);
        }else {
            prop.setMode(Mode::AUTOMATIC);
            prop.setPosition(msg->getContent().substring(1, 3).toInt());
        }
        
    }
}

void SerialCommTask::send(){
    currentState = State::RECEIVE;
    String message;
    if (prop.getMode() == Mode::MANUAL){
        message = "M" + (String)prop.getPos();
    } else{
        message = "A";
    }
    
    MsgService.sendMsg(message);
}