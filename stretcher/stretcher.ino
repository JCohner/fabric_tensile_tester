#include <fast_samd21_tc3.h>
#include <fast_samd21_tc4.h>

#include "robot.h"

Robot robot;

void TC3_Handler(void) {
  robot.tick_rail();
  TC3->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void TC4_Handler(void) {
  robot.tick_load_cell();
  TC4->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void setup() {
  while (!Serial){
    ;
  }

  robot.setup();

  pinMode(LED_BUILTIN, OUTPUT);
  fast_samd21_tc3_configure(2000); // starts the timer/trigger with 2ms
  fast_samd21_tc4_configure(20); // starts the timer/trigger with 20us
  Serial.begin(9600);
}

void loop() {
  delay(10);
  if (Serial.available() > 0){
    auto incoming_string = Serial.readStringUntil('\r');
    Serial.print("Read string: ");
    Serial.println(incoming_string);

    robot.enqueue_message(incoming_string);
  }
  robot.tick();
}

