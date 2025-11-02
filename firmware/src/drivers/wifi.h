#pragma once

#include <WiFiManager.h>
#include <string>

class WiFiDriver {
  public:
    void begin(std::string hostname, std::string ssid, std::string password);
    bool connected();

  private:
    WiFiManager wifiManager;
};
