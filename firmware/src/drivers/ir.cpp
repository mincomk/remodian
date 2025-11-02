#include "ir.h"
#include "HardwareSerial.h"

RC5IRDriver::RC5IRDriver(uint16_t pin, uint8_t address)
    : address(address), irsend(pin) {}

void RC5IRDriver::begin() { irsend.begin(); }

void RC5IRDriver::send(uint8_t command) {
    uint16_t frame = irsend.encodeRC5X(address, command, toggle);

    Serial.print("Frame: ");
    Serial.println(frame);

    irsend.sendRC5(frame);
    toggle = !toggle;
}
