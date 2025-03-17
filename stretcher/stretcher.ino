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
  Serial1.begin(9600); // debug out
  while (!Serial){
    ;
  }

  robot.setup();

  pinMode(LED_BUILTIN, OUTPUT);
  fast_samd21_tc3_configure(2000); // starts the timer/trigger with 2ms
  fast_samd21_tc4_configure(20); // starts the timer/trigger with 20us // TODO deactivate this if we arent reading LC
  fast_samd21_tc5_configure(10000); // starts the timer/trigger with 10ms
}

char yuh[100] = {0};
int ii = 0;
char termination_char = '\r';

void loop() {
  delay(100);
  // if command available write
  if (Serial.available() > 0){
    auto incoming_byte = Serial.read();
    yuh[ii++] = incoming_byte;
    Serial1.print("Read byte: ");
    Serial1.println(incoming_byte);

    if (incoming_byte == termination_char){
      Serial1.print("Read string: ");
      Serial.println(yuh);
      robot.enqueue_message(yuh);
      memset(yuh, 0, 100*sizeof(char));
      ii =0;
    }

  }

  //get and publish state update
  char mess[250] = {0};
  robot.post_update(mess);
  Serial.print(mess);
}

