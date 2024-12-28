#include <cmath>

#include "rail.h"

void Rail::setup_stepper(){
  // custom pins
  stepper.settings.standbyPin = 8;
  stepper.settings.enablePin = 4;
  stepper.settings.mode0Pin = 6;
  stepper.settings.mode1Pin = 5;
  stepper.settings.mode2Pin = 9;
  stepper.settings.mode3Pin = 10;
  stepper.settings.errorPin = 7; // maybe should be int pin
  // set resolution
  stepper.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_FIXED_1_32;
  stepper.settings.stepResolution = PRODRIVER_STEP_RESOLUTION_1_32;
  stepper.begin(); // stepper.call control_mode_select() which sets MODE pins and releases STNDBY
}

void Rail::setup(){
  setup_stepper();
}

void Rail::move(double pos){
  double dist_mm = pos - rail_position_;
  int dist_steps = std::floor(dist_mm * get_step_per_mm());
  is_moving_ = true;
  stepper.step(std::abs(dist_steps) , std::signbit(dist_steps));
  is_moving_ = false;
}

double Rail::get_step_per_mm(){
  return stepper.settings.stepResolution * rail_pitch_ * base_step_per_rev;
}