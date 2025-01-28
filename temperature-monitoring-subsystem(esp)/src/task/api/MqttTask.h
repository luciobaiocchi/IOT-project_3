#ifndef MQTTTASK_H
#define MQTTTASK_H

#include <PubSubClient.h>
#include <WiFi.h>
#include "./config/config.h"
#include "./data/api/SharedState.h"

class MqttTask {
public:
    MqttTask(const char* mqttServer, 
            int mqttPort, 
            const char* clientId, 
            SharedState& sharedState);

    void update();

private:
    const char* mqttServer;
    int mqttPort;
    const char* clientId;
    SharedState& sharedState;

    WiFiClient wifiClient;
    PubSubClient mqttClient;

    void connectToWiFi();
    void connectToMqtt();
};

#endif

