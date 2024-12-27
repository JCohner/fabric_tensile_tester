#line 1 "/home/jambox/dev/stretch_me/stretcher/stepper.cpp"
#include "stepper.h"

void Stepper::setup(){
  // Let's setup some non-default pins to use!
  // Note, to setup any non-default settings, you much do this before you call .begin()
  myProDriver.settings.standbyPin = 8;
  myProDriver.settings.enablePin = 4;
  myProDriver.settings.mode0Pin = 6;
  myProDriver.settings.mode1Pin = 5;
  myProDriver.settings.mode2Pin = 9;
  myProDriver.settings.mode3Pin = 10;
  myProDriver.settings.errorPin = 7; // maybe should be int pin
  myProDriver.begin(); // custom pins defined above
}