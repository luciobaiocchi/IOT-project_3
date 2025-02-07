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

//max and min frequency
#define FS 1 // standard frequency
#define MIN_F 0.1 // one read every 10 sec (1/0.1 = 10)
#define MAX_F 2 // two read every 1 sec (1/2 = 0.5)
#define ONE_SECOND 1000 // period T of temperature reading

#define TS 0

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
