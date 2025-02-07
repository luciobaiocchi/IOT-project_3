#include "../api/TemperatureTask.h"

// Costruttore: inizializza il DHT11
TemperatureTask::TemperatureTask(int dhtPin, 
                                SharedState& state, 
                                SemaphoreHandle_t& sharedStateMutex)
    : state(NOT_CONNECT),
      dhtPin(dhtPin),
      dht(dhtPin, DHTTYPE),  // Inizializza il sensore DHT
      sharedState(state),
      sharedStateMutex(sharedStateMutex) {
    dht.begin();  // Avvia il sensore
}

void TemperatureTask::update() {
    unsigned long currentTime = millis();
    int period = 0;

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
            //calcolo il periodo facendo 1sec/freq 
            period = ONE_SECOND / sharedState.getFrequency();
            // Leggi dal DHT11 solo se è passato il tempo definito dalla frequenza
            if (currentTime - sharedState.getLastReadTime() >= period) {
                float temperature = dht.readTemperature();  // Lettura temperatura
                // Verifica che la lettura sia valida
                if (!isnan(temperature)) {
                    sharedState.setTemperature((int)temperature);
                    currentTime = millis();
                    sharedState.setLastReadTime((unsigned long)currentTime);
                }
            }
            xSemaphoreGive(sharedStateMutex);
            break;
        default:
            break;
    }
}