#pragma once

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <cstdint>
#include <functional>
#include <map>
#include <string>

typedef std::function<void(JsonDocument &doc)> MQTTCallback;

class MQTTDriver {
  public:
    MQTTDriver(std::string server, uint16_t port);

    void begin();
    void loop();
    void publish(std::string topic, std::string &message);
    void setCallback(std::string topic, MQTTCallback callback);

  private:
    void reconnect();
    void onMessage(std::string topic, byte *payload, unsigned int length);

    WiFiClient wifiClient;
    PubSubClient mqttClient;
    std::string server;
    uint16_t port;
    std::map<std::string, MQTTCallback> topicHandlers;
};
