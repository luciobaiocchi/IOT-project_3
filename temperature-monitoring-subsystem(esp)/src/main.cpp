#include <Arduino.h>

// Definizione dell'oggetto condiviso
typedef struct {
    float temperature;       // Temperatura corrente
    int systemState;         // Stato del sistema (NORMALE, CALDO, TROPPO CALDO)
    int samplingFrequency;   // Frequenza di campionamento (F1 o F2)
    bool networkStatus;      // Stato della rete (true = attiva, false = problemi)
    SemaphoreHandle_t mutex; // Mutex per l'accesso atomico
} SystemStatus;


// Enum per gli stati del sistema
enum SystemState {
    NORMAL_STATE,
    HOT_STATE,
    TOO_HOT_STATE
};

// Costanti per le frequenze di campionamento
#define F1 1000  // 1 secondo
#define F2 500   // 0.5 secondi

// Funzione per aggiornare l'oggetto condiviso in modo atomico
void updateSharedData(float temperature, int state, int frequency, bool networkStatus) {
    xSemaphoreTake(systemStatus.mutex, portMAX_DELAY);
    systemStatus.temperature = temperature;
    systemStatus.systemState = state;
    systemStatus.samplingFrequency = frequency;
    systemStatus.networkStatus = networkStatus;
    xSemaphoreGive(systemStatus.mutex);
}

// Task Lettura Temperatura
void vTemperatureReadTask(void *pvParameters) {
    while (1) {
        float temperature = readTemperatureSensor(); // Funzione per leggere il sensore
        xSemaphoreTake(systemStatus.mutex, portMAX_DELAY);
        int frequency = systemStatus.samplingFrequency; // Legge la frequenza corrente
        xSemaphoreGive(systemStatus.mutex);
        updateSharedData(temperature, -1, -1, -1); // Aggiorna solo la temperatura
        vTaskDelay(pdMS_TO_TICKS(frequency)); // Aspetta in base alla frequenza
    }
}

// Task Scrittura LED
void vLEDWriteTask(void *pvParameters) {
    while (1) {
        xSemaphoreTake(systemStatus.mutex, portMAX_DELAY);
        int state = systemStatus.systemState;
        bool networkStatus = systemStatus.networkStatus;
        xSemaphoreGive(systemStatus.mutex);

        if (networkStatus) {
            setGreenLED(true);  // LED verde acceso
            setRedLED(false);   // LED rosso spento
        } else {
            setGreenLED(false); // LED verde spento
            setRedLED(true);    // LED rosso acceso
        }
        vTaskDelay(pdMS_TO_TICKS(500)); // Controlla i LED ogni 500 ms
    }
}

// Task Comunicazione MQTT
void vMQTTCommunicationTask(void *pvParameters) {
    while (1) {
        xSemaphoreTake(systemStatus.mutex, portMAX_DELAY);
        float temperature = systemStatus.temperature;
        xSemaphoreGive(systemStatus.mutex);

        sendTemperatureViaMQTT(temperature); // Funzione per inviare dati MQTT
        vTaskDelay(pdMS_TO_TICKS(1000)); // Invia dati ogni secondo
    }
}

// Task Gestione Frequenza
void vFrequencyManagementTask(void *pvParameters) {
    while (1) {
        xSemaphoreTake(systemStatus.mutex, portMAX_DELAY);
        float temperature = systemStatus.temperature;
        xSemaphoreGive(systemStatus.mutex);

        int newState, newFrequency;
        if (temperature < T1) {
            newState = NORMAL_STATE;
            newFrequency = F1;
        } else if (temperature >= T1 && temperature <= T2) {
            newState = HOT_STATE;
            newFrequency = F2;
        } else {
            newState = TOO_HOT_STATE;
            newFrequency = F2;
        }

        updateSharedData(-1, newState, newFrequency, -1); // Aggiorna solo stato e frequenza
        vTaskDelay(pdMS_TO_TICKS(1000)); // Controlla lo stato ogni secondo
    }
}

void setup() {
    // Inizializzazione dell'oggetto condiviso
    systemStatus.mutex = xSemaphoreCreateMutex();
    systemStatus.temperature = 0.0;
    systemStatus.systemState = NORMAL_STATE;
    systemStatus.samplingFrequency = F1;
    systemStatus.networkStatus = true;

    // Creazione dei task
    xTaskCreate(vTemperatureReadTask, "TempRead", 2048, NULL, 1, NULL);
    xTaskCreate(vLEDWriteTask, "LEDWrite", 1024, NULL, 1, NULL);
    xTaskCreate(vMQTTCommunicationTask, "MQTTComm", 2048, NULL, 1, NULL);
    xTaskCreate(vFrequencyManagementTask, "FreqMgmt", 2048, NULL, 1, NULL);
}

void loop() {
    // Il loop principale è vuoto perché tutto è gestito dai task
}