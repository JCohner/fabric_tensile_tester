#include <cmath>

#include <Arduino.h>
#include "rail.h"

void Rail::setup_stepper(){
  // custom pins for stepper
  stepper.settings.standbyPin = 8;
  stepper.settings.enablePin = 4;
  stepper.settings.mode0Pin = 6;
  stepper.settings.mode1Pin = 5;
  stepper.settings.mode2Pin = 9;
  stepper.settings.mode3Pin = 10;
  stepper.settings.errorPin = 7; // maybe should be int pin
  // set resolution
  //stepper.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_FIXED_1_1;
  //stepper.settings.stepResolution = PRODRIVER_STEP_RESOLUTION_1_1;
  stepper.begin(); // stepper.call control_mode_select() which sets MODE pins and releases STNDBY

  // configure homing switch
  pinMode(HOMING_PIN, INPUT);
}

void Rail::setup(){
  setup_stepper();
}

void Rail::move_absolute(double pos){
  double dist_mm = pos - rail_position_;
  Serial.print("Moving rail: ");
  Serial.println(dist_mm);
  int dist_steps = std::floor(dist_mm * get_step_per_mm());
  Serial.print("Commanding this many steps: ");
  Serial.println(dist_steps);
  is_moving_ = true;
  auto ret = stepper.step(abs(dist_steps) , std::signbit(dist_steps));
  Serial.print("Moved completed successfully?: ");
  Serial.println(ret);
  is_moving_ = false;
  rail_position_ = pos;
}

void Rail::move_relative(double pos){
  Serial.print("Moving rail relative: ");
  Serial.print(pos);
  Serial.print("mm from: ");
  Serial.println(rail_position_);
  move_absolute(rail_position_ + pos);
}

double Rail::get_step_per_mm(){
  return stepper.settings.stepResolution * (1.0 / rail_pitch_) * base_step_per_rev;
}

bool Rail::is_home_switch_hit(){
  return digitalRead(HOMING_PIN);
}