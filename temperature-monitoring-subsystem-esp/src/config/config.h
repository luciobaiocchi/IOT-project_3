#ifndef CONFIG_H
#define CONFIG_H

// Pin hardware
#define DHT_PIN 5
#define TEMP_SENSOR_PIN 34
#define LED_GREEN_PIN 2
#define LED_RED_PIN 4

// Wifi network info
#define WIFI_SSID "lucio"
#define WIFI_PASSWORD "lupolucio"

// MQTT network info
#define MQTT_SERVER "broker.mqtt-dashboard.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "temperatureSensor"
#define MQTT_CLIENT_ID "ESP32-TempSensor"

// Topic 
#define SEND_TOPIC "temperature"
#define RECIVE_TOPIC "frequency"

//State

enum TaskState{
    CONNECT,
    NOT_CONNECT
};

enum MqttTaskState{
    WIFI_CONNECTING,
    MQTT_CONNECTING,
    CONNECTED
};

#endif
