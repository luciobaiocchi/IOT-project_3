#ifndef CONFIG_H
#define CONFIG_H

// Pin hardware
#define TEMP_SENSOR_PIN 34
#define LED_GREEN_PIN 2
#define LED_RED_PIN 4

// Wifi network info
#define WIFI_SSID "FilippoMassari"
#define WIFI_PASSWORD "87654321"

// MQTT network info
#define MQTT_SERVER "broker.mqtt-dashboard.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "temperatureSensor"
#define MQTT_CLIENT_ID "ESP32-TempSensor"

// Topic 
#define SEND_TOPIC "temperature"
#define RECIVE_TOPIC "frequency"

#endif
