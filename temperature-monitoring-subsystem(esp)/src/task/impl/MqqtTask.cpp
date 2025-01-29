#include "../api/MqttTask.h"

MqttTask::MqttTask(const char* mqttServer, int mqttPort, const char* clientId, SharedState& sharedState)
    : mqttServer(mqttServer), mqttPort(mqttPort), clientId(clientId), sharedState(sharedState),
      mqttClient(wifiClient), lastMsgTime(0) {
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(onMessageReceived);
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
    }

    sharedState.setWifiNetworkConnected(true);
    Serial.println("\nConnesso al WiFi!");
    Serial.print("Indirizzo IP: ");
    Serial.println(WiFi.localIP());
}

void MqttTask::connectToMqtt() {
    Serial.println("Connessione al server MQTT...");
    
    while (!mqttClient.connected()) {
        String clientId = String("esp32-client-") + String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str())) {
            sharedState.setMqttNetworkConnected(true);
            Serial.println("Connesso a MQTT!");
            mqttClient.subscribe(RECIVE_TOPIC);
            Serial.println(String("Iscrittto al topic ") + RECIVE_TOPIC);
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

    unsigned long now = millis();
    if (now - lastMsgTime > sharedState.getFrequency()) {
        lastMsgTime = now;

        char msg[MSG_BUFFER_SIZE];
        String tempMsg = "Temperatura: " + String(sharedState.getTemperature()) + "°C";
        snprintf(msg, MSG_BUFFER_SIZE, "%s", tempMsg.c_str());

        Serial.println(String("Pubblicazione messaggio: ") + msg);
        publishMessage(SEND_TOPIC, msg);
    }
}

void MqttTask::publishMessage(const char* topic, const char* message) {
    mqttClient.publish(topic, message);
}

void MqttTask::onMessageReceived(char* topic, byte* payload, unsigned int length) {
    Serial.print("Messaggio ricevuto su [");
    Serial.print(topic);
    Serial.print("]: ");
    
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println(message);
}
