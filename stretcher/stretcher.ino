#include <fast_samd21_tc3.h>
#include <fast_samd21_tc4.h>
#include <fast_samd21_tc5.h>

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

void TC5_Handler(void) {
    robot.tick();
  TC5->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial){
    ;
  }

  robot.setup();

  pinMode(LED_BUILTIN, OUTPUT);
  fast_samd21_tc3_configure(2000); // starts the timer/trigger with 2ms
  fast_samd21_tc4_configure(20); // starts the timer/trigger with 20us // TODO deactivate this if we arent reading LC
  fast_samd21_tc5_configure(10000); // starts the timer/trigger with 10ms
}

void loop() {
  delay(100);
  // if command available write
  if (Serial.available() > 0){
    auto incoming_string = Serial.readStringUntil('\r');
    Serial.print("Read string: ");
    Serial.println(incoming_string);

    robot.enqueue_message(incoming_string);
  }
  //get and publish state update
  char mess[250] = {0};
  robot.post_update(mess);
  Serial1.print(mess);
}

