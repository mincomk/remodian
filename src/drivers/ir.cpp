#include "ir.h"

RC5IRDriver::RC5IRDriver(uint16_t pin, uint8_t address)
    : address(address), irsend(pin) {}

uint16_t buildRC5Frame(uint8_t address, uint8_t command, uint8_t toggle) {
    uint16_t frame = (0x3 << 12) | ((toggle & 0x1) << 11) |
                     ((address & 0x1F) << 6) | (command & 0x3F);
    return frame;
}

void RC5IRDriver::begin() { irsend.begin(); }

void RC5IRDriver::send(uint8_t command) {
    uint16_t frame = buildRC5Frame(address, command, toggle);
    irsend.sendRC5(frame);
    toggle ^= 1;
}
