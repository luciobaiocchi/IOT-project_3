#include "../api/TemperatureTask.h"

// Costruttore: inizializza il DHT11
TemperatureTask::TemperatureTask(int dhtPin, 
                                SharedState& state, 
                                SemaphoreHandle_t& sharedStateMutex)
    : state(NOT_CONNECT),
    sensor(sensorPin), 
    sharedState(state),
    sharedStateMutex(sharedStateMutex) {
    pinMode(sensorPin, INPUT);
}

void TemperatureTask::update() {
    unsigned long currentTime = millis();

    // Acquisisci il mutex per accedere allo stato condiviso
    while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    // Verifica lo stato della connessione
    if (sharedState.isMqttNetworkConnected()) {
        state = CONNECT;
    } else {
        state = NOT_CONNECT;
    }

    xSemaphoreGive(sharedStateMutex);

    switch (state) {
        case CONNECT:
            // Acquisisci il mutex per leggere/scrivere dati
            while (!xSemaphoreTake(sharedStateMutex, pdMS_TO_TICKS(5000))) {
                vTaskDelay(pdMS_TO_TICKS(100));
            }

            // Leggi dal DHT11 solo se è passato il tempo definito dalla frequenza
            if (currentTime - sharedState.getLastReadTime() >= sharedState.getFrequency()) {
                float temperature = dht.readTemperature();  // Lettura temperatura
                Serial.print("temp");
                Serial.println((int)temperature);

                // Verifica che la lettura sia valida
                if (!isnan(temperature)) {
                    sharedState.setTemperature((int)temperature);
                    sharedState.setLastReadTime((int)currentTime);
                }
            }

            xSemaphoreGive(sharedStateMutex);
            break;

        default:
            break;
    }
}