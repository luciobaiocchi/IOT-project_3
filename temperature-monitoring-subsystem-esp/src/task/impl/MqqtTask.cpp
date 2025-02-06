#include "../api/MqttTask.h"

int n = 0;
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
    Serial.println("\nAvvio connessione WiFi...");
    
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    vTaskDelay(pdMS_TO_TICKS(100));
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        Serial.print(".");
    }

    while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    sharedState.setWifiNetworkConnected(true);
    xSemaphoreGive(sharedStateMutex);

    Serial.println("\nConnesso al WiFi!");
    Serial.print("Indirizzo IP: ");
    Serial.println(WiFi.localIP());
}

void MqttTask::connectToMqtt() {
    Serial.println("Connessione al server MQTT...");
    
    while (!mqttClient.connected()) {
        String clientId = String("esp32-client-") + String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str())) {
            while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                vTaskDelay(pdMS_TO_TICKS(100));
            }

            sharedState.setMqttNetworkConnected(true);
            xSemaphoreGive(sharedStateMutex);

            Serial.println("Connesso a MQTT!");
            mqttClient.subscribe(RECIVE_TOPIC);
            Serial.println(String("Iscritto al topic ") + RECIVE_TOPIC);
        } else {
            Serial.print("Connessione fallita, rc=");
            Serial.print(mqttClient.state());
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
    }
}

void MqttTask::onMessageReceived(char* topic, byte* payload, unsigned int length) {

    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println(message);

    int newFrequency = message.toInt();
    if (newFrequency > 0) {
        receivedFrequency = newFrequency;
    } else {
        Serial.println("Errore: valore di frequenza non valido");
    }
}

void MqttTask::publishMessage(const char* topic, const char* message) {
    mqttClient.publish(topic, message);
}

void MqttTask::update() {
    if (WiFi.status() != WL_CONNECTED) {
        state = WIFI_CONNECTING;
    } else if (!mqttClient.connected()) {
        state = MQTT_CONNECTING;
    } else {
        state = CONNECTED;
    }


    switch (state) {
        case WIFI_CONNECTING:
            while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                vTaskDelay(pdMS_TO_TICKS(100));
            }
            sharedState.setWifiNetworkConnected(false);
            xSemaphoreGive(sharedStateMutex);
            connectToWiFi();
            break;

        case MQTT_CONNECTING:
            while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                vTaskDelay(pdMS_TO_TICKS(100));
            }
            sharedState.setMqttNetworkConnected(false);
            xSemaphoreGive(sharedStateMutex);
            connectToMqtt();
            break;

        case CONNECTED:
            mqttClient.loop();

            if (receivedFrequency > 0 && receivedFrequency != sharedState.getFrequency()) {
                while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                    vTaskDelay(pdMS_TO_TICKS(100));
                }

                sharedState.setFrequency(receivedFrequency);
                Serial.println("Frequenza aggiornata in sharedState: " + String(receivedFrequency));
                receivedFrequency = 0;

                xSemaphoreGive(sharedStateMutex);
            }


            unsigned long now = millis();
            if (now - lastMsgTime > sharedState.getFrequency()) {

                while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                    vTaskDelay(pdMS_TO_TICKS(100));
                }

                lastMsgTime = now;

                char msg[MSG_BUFFER_SIZE];
                int tempMsg = sharedState.getTemperature();
                snprintf(msg, MSG_BUFFER_SIZE, "%d", tempMsg);

                xSemaphoreGive(sharedStateMutex);

                publishMessage(SEND_TOPIC, msg);
            }
            break;
    }
}
