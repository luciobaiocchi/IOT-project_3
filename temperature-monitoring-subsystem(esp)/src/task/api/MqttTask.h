#ifndef MQTTTASK_H
#define MQTTTASK_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "./config/config.h"
#include "./data/api/SharedState.h"

#define MSG_BUFFER_SIZE 50

class MqttTask {
public:
    MqttTask(const char* mqttServer, int mqttPort, const char* clientId, SharedState& sharedState);

    void update();
    void publishMessage(const char* topic, const char* message);

private:
    const char* mqttServer;
    int mqttPort;
    const char* clientId;
    SharedState& sharedState;

    WiFiClient wifiClient;
    PubSubClient mqttClient;
    unsigned long lastMsgTime;

    void connectToWiFi();
    void connectToMqtt();
    static void onMessageReceived(char* topic, byte* payload, unsigned int length);
};

#endif
