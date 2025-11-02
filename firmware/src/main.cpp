#include "HardwareSerial.h"
#include "config.h"
#include "drivers/ir.h"
#include "drivers/irrecv.h"
#include "drivers/mqtt.h"
#include "drivers/wifi.h"
#include "esp32-hal.h"
#include "hardware.h"
#include <ArduinoJson.h>

WiFiDriver wifi;
RC5IRDriver ir(IR_SEND_PIN, RC5_ADDRESS);
MQTTDriver mqtt(MQTT_BROKER_HOST, MQTT_BROKER_PORT);
IRReceiverDriver irrecv(IR_RECV_PIN);

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
    irrecv.begin();
    mqtt.begin();
    mqtt.setCallback(MQTT_CMD_TOPIC, handlePacket);
}

void loop() {
    mqtt.loop();

    auto decoded = irrecv.decode();
    if (decoded) {
        auto str = resultsToString(decoded.value());
        Serial.println(str.c_str());
        mqtt.publish(MQTT_IR_TOPIC, str);
    }
}
