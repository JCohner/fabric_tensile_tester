#include <fast_samd21_tc3.h>

#include "stepper.h"

Stepper step;

void TC3_Handler(void) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  TC3->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  fast_samd21_tc3_configure(100000); // starts the timer/trigger with 0.1 s
  step.setup();

  Serial.begin(9600);
}

void loop() {
  delay(10);
  Serial.println(analogRead(A7));
}
