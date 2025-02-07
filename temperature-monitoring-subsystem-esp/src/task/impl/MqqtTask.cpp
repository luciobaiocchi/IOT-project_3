#include "../api/MqttTask.h"

MqttTask::MqttTask(const char* mqttServer, 
                 int mqttPort, 
                 const char* clientId, 
                 SharedState& sharedState,
                 SemaphoreHandle_t& sharedStateMutex)
    : state(WIFI_CONNECTING),
    mqttServer(mqttServer), 
    mqttPort(mqttPort), 
    clientId(clientId), 
    sharedState(sharedState),
    mqttClient(wifiClient), 
    lastMsgTime(0), 
    receivedFrequency(0),
    sharedStateMutex(sharedStateMutex) {

    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->onMessageReceived(topic, payload, length);
    });
}

void MqttTask::connectToWiFi() {
    Serial.println("\nConnessione WiFi in corso...");
    
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    vTaskDelay(pdMS_TO_TICKS(100));
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        Serial.print(".");
    }

    if(xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
        sharedState.setWifiNetworkConnected(true);
        xSemaphoreGive(sharedStateMutex);
    }

    Serial.println("\nWiFi connesso");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

void MqttTask::connectToMqtt() {
    Serial.println("Connessione MQTT...");
    
    while (!mqttClient.connected()) {
        String clientId = String("esp32-") + String(random(0xffff), HEX);

        if(mqttClient.connect(clientId.c_str())) {
            if(xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                sharedState.setMqttNetworkConnected(true);
                xSemaphoreGive(sharedStateMutex);
            }
            
            mqttClient.subscribe(RECIVE_TOPIC);
            Serial.println("Connesso al broker MQTT");
            break;
        }
        
        Serial.print("Errore connessione MQTT: ");
        Serial.println(mqttClient.state());
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void MqttTask::onMessageReceived(char* topic, byte* payload, unsigned int length) {
    char buffer[10];
    size_t len = min(length, sizeof(buffer)-1);
    memcpy(buffer, payload, len);
    buffer[len] = '\0';

    int newFreq = atoi(buffer);
    if(newFreq >= MIN_F && newFreq <= MAX_F) {  // Frequenza valida tra 1 e 60 secondi
        receivedFrequency = newFreq;
        Serial.print("Frequenza ricevuta");
        Serial.println(receivedFrequency);
    } else {
        Serial.println("Frequenza non valida");
    }
}

void MqttTask::publishMessage(const char* topic, const char *value) {
    char msg[4];
    snprintf(msg, sizeof(msg), "%d", value);
    mqttClient.publish(topic, msg);
    Serial.print("SEND :");
    Serial.println(msg);

}


void MqttTask::update() {
    // Aggiorna lo stato della connessione
    state = (!WiFi.isConnected()) ? WIFI_CONNECTING : 
           (!mqttClient.connected()) ? MQTT_CONNECTING : CONNECTED;

    switch(state) {
        case WIFI_CONNECTING:
            if(xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                sharedState.setWifiNetworkConnected(false);
                xSemaphoreGive(sharedStateMutex);
            }
            connectToWiFi();
            break;

        case MQTT_CONNECTING:
            if(xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                sharedState.setMqttNetworkConnected(false);
                xSemaphoreGive(sharedStateMutex);
            }
            connectToMqtt();
            break;

        case CONNECTED:
            mqttClient.loop();

            // Aggiorna la frequenza se necessario
            if(receivedFrequency > 0 && receivedFrequency != sharedState.getFrequency()) {
                if(xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                    sharedState.setFrequency(receivedFrequency);
                    Serial.printf("Nuova frequenza: %d ms\n", receivedFrequency);
                    receivedFrequency = 0;
                    xSemaphoreGive(sharedStateMutex);
                }
            }

            // Invia il dato termico
            unsigned long now = millis();
            if(now - lastMsgTime >= sharedState.getFrequency()) {
                if(xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                    int temperature = sharedState.getTemperature();
                    
                    // Clamping del valore tra -30 e 50
                    temperature = constrain(temperature, -30, 50);
                    
                    publishMessage(SEND_TOPIC, (char*)temperature);
                    lastMsgTime = now;
                    xSemaphoreGive(sharedStateMutex);
                }
            }
            break;
    }
}