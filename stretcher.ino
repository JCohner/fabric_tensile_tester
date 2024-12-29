#include <fast_samd21_tc3.h>

#include "user_interface.h"
#include "robot.h"

Robot robot;

void TC3_Handler(void) {
  //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  //Serial.println(analogRead(A7));
  robot.tick();
  TC3->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void TC4_Handler(void) {
  check_for_commands();
  TC4->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void setup() {
  while (!Serial){
    ;
  }

  robot.setup();

  pinMode(LED_BUILTIN, OUTPUT);
  fast_samd21_tc3_configure(100000); // starts the timer/trigger with 0.1 s
  //fast_samd21_tc4_configure(100000); // starts the timer/trigger with 0.1 s
  Serial.begin(9600);
}

void loop() {
  auto command = check_for_commands();
  if (command != Robot::Command::NONE){
    robot.enqueue_command(command);
  }
}

