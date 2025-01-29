#include "SerialCommTask.h"

SerialCommTask::SerialCommTask(Properties& prop) : prop(prop) {
    MsgService.init();
    currentState = State::SEND;
}

void SerialCommTask::init(int period){
    Task::init(period);   
}

/*  Messaggio --> M0000 */
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
        if (msg->getContent().charAt(0) != prop.getCharMode()){
            prop.setMode(msg->getContent().charAt(0));
        }
        if (msg->getContent().substring(1, 4).toInt() != prop.getPos()){
            prop.setPosition(msg->getContent().substring(1, 4).toInt());
            prop.setTemp(msg->getContent().substring(4, 6).toInt());
        }
    }
}

void SerialCommTask::send(){
    String message = "" + prop.getCharMode() + prop.getPos();
    MsgService.sendMsg(message);
}