#ifndef SHAREDSTATE_H
#define SHAREDSTATE_H

#include <Arduino.h>

class SharedState {
public:
    SharedState();

    int getTemperature() const;
    void setTemperature(int temp);

    int getFrequency() const;
    void setFrequency(int freq);

    bool isWifiNetworkConnected() const;
    void setWifiNetworkConnected(bool status);

    bool isMqttNetworkConnected() const;
    void setMqttNetworkConnected(bool status);

    unsigned long getLastReadTime() const;
    void setLastReadTime(unsigned long time);

private:
    int temperature;
    int frequency;
    bool wifiNetwork;
    bool mqttNetwork;
    unsigned long lastReadTime;
};

#endif
