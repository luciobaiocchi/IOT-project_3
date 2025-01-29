#include "../api/MqttTask.h"

MqttTask::MqttTask(const char* mqttServer, 
                    int mqttPort, const char* clientId, 
                    SharedState& sharedState)

    : mqttServer(mqttServer), 
    mqttPort(mqttPort), 
    clientId(clientId), 
    sharedState(sharedState), 
    mqttClient(wifiClient) {
    mqttClient.setServer(mqttServer, mqttPort);
}

void MqttTask::connectToWiFi() {
    Serial.println("\nAvvio connessione WiFi...");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        delay(1000);
        Serial.print(".");
        delay(1000);
        Serial.println(".");
    }

    sharedState.setWifiNetworkConnected(true);
    Serial.println("\nConnesso al WiFi!");
    Serial.print("Indirizzo IP: ");
    Serial.println(WiFi.localIP());
}

void MqttTask::connectToMqtt() {
    while (!mqttClient.connected()) {
        Serial.print("Connessione al server MQTT... ");
        if (mqttClient.connect(clientId)) {
            sharedState.setMqttNetworkConnected(true);
            Serial.println("Connesso!");
            mqttClient.subscribe("example/topic"); // add real topic
        } else {
            Serial.print("Connessione fallita, rc=");
            Serial.print(mqttClient.state());
            Serial.println(". Riprovo tra 5 secondi...");
            delay(5000);
        }
    }
}

void MqttTask::update() {
    if (WiFi.status() != WL_CONNECTED) {
        sharedState.setWifiNetworkConnected(false);
        connectToWiFi();
    }

    if (!mqttClient.connected()) {
        sharedState.setMqttNetworkConnected(false);
        connectToMqtt();
    }

    mqttClient.loop();
}
