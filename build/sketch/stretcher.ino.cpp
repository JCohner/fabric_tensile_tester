#include <Arduino.h>
#line 1 "/home/jambox/dev/stretch_me/stretcher/stretcher.ino"
#include <fast_samd21_tc3.h>

#include "stepper.h"

Stepper step;

#line 7 "/home/jambox/dev/stretch_me/stretcher/stretcher.ino"
void TC3_Handler(void);
#line 12 "/home/jambox/dev/stretch_me/stretcher/stretcher.ino"
void setup();
#line 20 "/home/jambox/dev/stretch_me/stretcher/stretcher.ino"
void loop();
#line 7 "/home/jambox/dev/stretch_me/stretcher/stretcher.ino"
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
  /*
  myProDriver.step(200, 0); // turn 200 steps, CW direction
  delay(1000);
  myProDriver.step(200, 1); // turn 200 steps, CCW direction
  delay(1000);
  */
}

