#include "../api/SharedState.h"
#include "./config/config.h"

SharedState::SharedState()
    : temperature(TS), frequency(FS), wifiNetwork(false), mqttNetwork(false), lastReadTime(0) {
    }

int SharedState::getTemperature() const {
    return temperature;
}

void SharedState::setTemperature(int temp) {
    temperature = temp;
}

int SharedState::getFrequency() const {
    return frequency;
}

void SharedState::setFrequency(int freq) {
    frequency = freq;
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

