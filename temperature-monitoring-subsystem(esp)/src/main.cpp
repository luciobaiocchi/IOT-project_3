#include <Arduino.h>

#include "./data/api/SharedState.h"
#include "./task/api/LedTask.h"
#include "./task/api/TemperatureTask.h"
#include "./task/api/MqttTask.h"

SharedState sharedState;

/*LedTask ledTask(LED_GREEN_PIN, LED_RED_PIN, sharedState);
TemperatureTask temperatureTask(TEMP_SENSOR_PIN, sharedState);*/
MqttTask mqttTask(MQTT_SERVER, MQTT_PORT, MQTT_CLIENT_ID, sharedState);

void setup() {
    Serial.begin(9600);
    /*ledTask.init();
    temperatureTask.init();*/
    mqttTask.update();
}

void loop() {
    /*ledTask.update();
    temperatureTask.update();*/
    mqttTask.update();

    delay(100);
}
