#pragma once

#include "IRsend.h"
#include <cstdint>
class RC5IRDriver {
  public:
    RC5IRDriver(uint16_t pin, uint8_t address);

    void begin();
    void send(uint8_t command);

  private:
    uint8_t address;
    uint8_t toggle = 0;
    IRsend irsend;
};
