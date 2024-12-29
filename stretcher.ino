#include <fast_samd21_tc3.h>
#include "rail.h"

Rail rail;

void TC3_Handler(void) {
  //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  //Serial.println(analogRead(A7));
  TC3->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void setup() {
  while (!Serial){
    ;
  }

  pinMode(LED_BUILTIN, OUTPUT);
  fast_samd21_tc3_configure(100000); // starts the timer/trigger with 0.1 s
  rail.setup();

  Serial.begin(9600);
}

void loop() {
  char buff[50]; 
  int i = 0;
  if (Serial.available() > 0){
    auto incoming_string = Serial.readStringUntil('\r');
    Serial.print("Rail at: ");
    Serial.println(rail.get_position());
    Serial.print("Sending rail to: ");
    auto pos = atoi(incoming_string.c_str());
    Serial.println(pos);
    rail.move_absolute(pos);
    Serial.println("Rail move done ");
  }
}

