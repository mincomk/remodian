#include "HardwareSerial.h"
#include "config.h"
#include "drivers/ir.h"
#include "drivers/mqtt.h"
#include "drivers/wifi.h"
#include "esp32-hal.h"
#include "hardware.h"
#include <ArduinoJson.h>

WiFiDriver wifi;
RC5IRDriver ir(IR_PIN, RC5_ADDRESS);
MQTTDriver mqtt(MQTT_BROKER_HOST, MQTT_BROKER_PORT);

void fireCommand(uint8_t cmd) {
    for (int i = 0; i < COMMAND_FIRE_COUNT; i++) {
        ir.send(cmd);
        delay(50);
    }
}

void handlePacket(JsonDocument &doc) {
    if (doc["cmd"].is<int>()) {
        uint8_t cmd = doc["cmd"];
        Serial.println("Send!");
        Serial.println(cmd);

        fireCommand(cmd);
    } else {
        Serial.println("Invalid JSON: ");
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Hello!");

    wifi.begin(REMODIAN_HOSTNAME, AP_SSID, AP_PASSWORD);
    ir.begin();
    mqtt.begin();
    mqtt.setCallback(MQTT_TOPIC, handlePacket);
}

void loop() { mqtt.loop(); }
