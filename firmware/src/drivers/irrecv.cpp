#include "irrecv.h"
#include "IRutils.h"
#include <string>

IRReceiverDriver::IRReceiverDriver(uint16_t pin) : irrecv(pin) {}

void IRReceiverDriver::begin() { irrecv.enableIRIn(); }

std::optional<decode_results> IRReceiverDriver::decode() {
    decode_results results;
    if (irrecv.decode(&results)) {
        irrecv.resume();
        return results;
    } else {
        return std::nullopt;
    }
}

std::string resultsToString(decode_results results) {
    std::string human = resultToHumanReadableBasic(&results).c_str();
    std::string code = resultToSourceCode(&results).c_str();

    return human + "\n\n" + code;
}
