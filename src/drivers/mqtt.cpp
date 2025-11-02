#include "mqtt.h"
#include "ArduinoJson/Document/JsonDocument.hpp"
#include "ArduinoJson/Json/JsonDeserializer.hpp"
#include "HardwareSerial.h"
#include "config.h"
#include "esp32-hal.h"

MQTTDriver::MQTTDriver(std::string server, uint16_t port)
    : mqttClient(wifiClient), server(server), port(port) {}

void MQTTDriver::begin() {
    mqttClient.setServer(server.c_str(), port);
    mqttClient.setCallback(
        [this](char *topic, byte *payload, unsigned int length) {
            this->onMessage(topic, payload, length);
        });
}

void MQTTDriver::loop() {
    if (!mqttClient.connected())
        reconnect();
    mqttClient.loop();
}

void MQTTDriver::publish(std::string topic, std::string &message) {
    mqttClient.publish(topic.c_str(), message.c_str());
}

void MQTTDriver::setCallback(std::string topic, MQTTCallback callback) {
    mqttClient.subscribe(topic.c_str());
    topicHandlers[topic] = callback;
}

void MQTTDriver::reconnect() {
    while (!mqttClient.connected()) {
        Serial.println("Connecting MQTT...");
        if (mqttClient.connect(MQTT_ID)) {
            Serial.println("Connected!");

            for (auto &pair : topicHandlers) {
                mqttClient.subscribe(pair.first.c_str());
            }
        } else {
            Serial.print("Failed. rc=");
            Serial.print(mqttClient.state());
            Serial.println(". Retrying in 2 seconds.");
            delay(2000);
        }
    }
}

void MQTTDriver::onMessage(std::string topic, byte *payload,
                           unsigned int length) {
    String msg;
    for (unsigned int i = 0; i < length; i++)
        msg += (char)payload[i];

    JsonDocument doc;
    if (deserializeJson(doc, msg)) {
        Serial.println("DeserializeJSON failed.");
        Serial.print("JSON: ");
        Serial.println(msg);
        return;
    };

    auto it = topicHandlers.find(topic);
    if (it != topicHandlers.end())
        it->second(doc);
}
