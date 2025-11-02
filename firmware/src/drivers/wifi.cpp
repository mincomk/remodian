#include "wifi.h"
#include "HardwareSerial.h"
#include <WiFi.h>
#include <WiFiType.h>

void WiFiDriver::begin(std::string hostname, std::string ssid,
                       std::string password) {
    Serial.println("Connecting WiFi...");
    WiFi.mode(WIFI_STA);
    if (wifiManager.autoConnect(ssid.c_str(), password.c_str())) {
        Serial.println("Connected!");
    } else {
        Serial.println("Connection failed.");
    }
    wifiManager.setHostname(hostname.c_str());
}

bool WiFiDriver::connected() { return WiFi.status() == WL_CONNECTED; }
