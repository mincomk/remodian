// Draft file just for signal debugging

#include <Arduino.h>
#include <IRrecv.h>
#include <IRutils.h>

#define RECV_PIN 12

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  while (!Serial) {
    ;
  }
  Serial.println("Hello, IR!");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(resultToHumanReadableBasic(&results));
    Serial.println(resultToSourceCode(&results));
    Serial.println();
    irrecv.resume();
  }
}
