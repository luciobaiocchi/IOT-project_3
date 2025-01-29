#include "../api/MqttClient.h"

MqttClient::MqttClient(const char* server, int port, const char* clientId)
    : mqttServer(server), mqttPort(port), mqttClientId(clientId), client(espClient) {
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
}

void MqttClient::connect() {
    while (!client.connected()) {
        if (client.connect(mqttClientId)) {
            Serial.println("MQTT Connected");
        } else {
            Serial.print("MQTT Connection failed, rc=");
            Serial.println(client.state());
            delay(5000);
        }
    }
}

void MqttClient::publish(const char* topic, const char* message) {
    client.publish(topic, message);
}

void MqttClient::subscribe(const char* topic) {
    client.subscribe(topic);
}

void MqttClient::loop() {
    client.loop();
}

void MqttClient::callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}
