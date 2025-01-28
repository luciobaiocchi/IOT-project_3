#ifndef SHAREDSTATE_H
#define SHAREDSTATE_H

#include <Arduino.h>

#define FS 1000
#define TS 0.0

class SharedState {
public:
    SharedState();

    float getTemperature() const;
    void setTemperature(float temp);

    int getReadFrequency() const;
    void setReadFrequency(int freq);

    bool isWifiNetworkConnected() const;
    void setWifiNetworkConnected(bool status);

    bool isMqttNetworkConnected() const;
    void setMqttNetworkConnected(bool status);

    unsigned long getLastReadTime() const;
    void setLastReadTime(unsigned long time);

private:
    float temperature;
    int readFrequency;
    bool wifiNetwork;
    bool mqttNetwork;
    unsigned long lastReadTime;
};

#endif
