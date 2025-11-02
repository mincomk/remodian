#pragma once

#include "IRrecv.h"
#include <cstdint>
#include <optional>

class IRReceiverDriver {
  public:
    IRReceiverDriver(uint16_t pin);

    void begin();
    std::optional<decode_results> decode();

  private:
    IRrecv irrecv;
};

std::string resultsToString(decode_results results);
