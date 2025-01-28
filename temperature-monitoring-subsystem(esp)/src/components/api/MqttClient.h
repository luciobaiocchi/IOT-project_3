#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <PubSubClient.h>
#include <WiFi.h>

class MqttClient {
public:
    MqttClient(const char* server, int port, const char* clientId);
    void connect();
    void publish(const char* topic, const char* message);
    void subscribe(const char* topic);
    void loop();

private:
    const char* mqttServer;
    int mqttPort;
    const char* mqttClientId;
    WiFiClient espClient;
    PubSubClient client;

    static void callback(char* topic, byte* payload, unsigned int length);
};

#endif
