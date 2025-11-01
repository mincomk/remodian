#include <Arduino.h>
#include <HardwareSerial.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("Hello, PlatformIO!");
}

void loop() {
  Serial.println("Looping...");
  delay(1000);
}
