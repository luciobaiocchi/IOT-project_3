#include "../api/SharedState.h"


SharedState::SharedState()
    : temperature(TS), readFrequency(FS), wifiNetwork(false), mqttNetwork(false), lastReadTime(0) {}

float SharedState::getTemperature() const {
    return temperature;
}

void SharedState::setTemperature(float temp) {
    temperature = temp;
}

int SharedState::getReadFrequency() const {
    return readFrequency;
}

void SharedState::setReadFrequency(int freq) {
    readFrequency = freq;
}

bool SharedState::isWifiNetworkConnected() const {
    return wifiNetwork;
}

void SharedState::setWifiNetworkConnected(bool status) {
    wifiNetwork = status;
}

bool SharedState::isMqttNetworkConnected() const {
    return mqttNetwork;
}

void SharedState::setMqttNetworkConnected(bool status) {
    mqttNetwork = status;
}

unsigned long SharedState::getLastReadTime() const {
    return lastReadTime;
}

void SharedState::setLastReadTime(unsigned long time) {
    lastReadTime = time;
}

