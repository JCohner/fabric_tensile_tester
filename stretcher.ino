#include <fast_samd21_tc3.h>

#include "robot.h"

Robot robot;

void TC3_Handler(void) {
  //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  //Serial.println(analogRead(A7));
  
  TC3->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void setup() {
  while (!Serial){
    ;
  }

  robot.setup();

  pinMode(LED_BUILTIN, OUTPUT);
  //fast_samd21_tc3_configure(10000); // starts the timer/trigger with 0.1 s
  //fast_samd21_tc4_configure(100000); // starts the timer/trigger with 0.1 s
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

