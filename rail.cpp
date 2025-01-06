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

void Rail::tick(){
  // if our current goal isn't running
  if (current_goal_.status.get() != Status::RUNNING){
    // try grab new command
    if (!job_queue_.empty()){
      current_goal_ = job_queue_.front();
      Serial.print("Got new rail goal of: ");
      Serial.println(current_goal_.position);
      job_queue_.pop();
    } else {
      return;
    }
  }



  // set running because we have a current goal
  current_goal_.status = Status::RUNNING;
  is_moving_ = true; // relic determine how and if we keep
  // if this is first pass
  if (current_goal_.status.check_edge(Status::NONE)){
    double dist_mm = current_goal_.position - rail_position_;
    Serial.print("Moving rail: ");
    Serial.println(dist_mm);
    int steps = std::floor(dist_mm * step_per_mm);
    current_goal_.steps_to_move = abs(steps);
    current_goal_.direction = std::signbit(steps);
    Serial.print("Commanding this many steps: ");
    Serial.println(current_goal_.steps_to_move);
  
    // enable stepper
    stepper.enable();
  }

  Serial.print("At this many steps: ");
  Serial.println(current_goal_.steps_moved);
  Serial.print("Out of: ");
  Serial.println(current_goal_.steps_to_move);
  bool err = false;
  if (current_goal_.steps_moved++ <= current_goal_.steps_to_move){
    err = non_blocking_step(current_goal_.direction);
    // if (current_goal_.direction){
    //   rail_position_ +=  1.0 / step_per_mm;
    // } else {
    //   rail_position_ -= 1.0 / step_per_mm;
    // }
  } else {
    current_goal_.status = Status::SUCCESS;
    is_moving_ = false;
    rail_position_ = current_goal_.position;
    stepper.disable();
  }

  if (!err){
    current_goal_.status = Status::FAILURE;
    is_moving_ = false;
    stepper.disable();
  }
}


bool Rail::non_blocking_step(bool direction){
  // set CW-CWW pin (aka mode3Pin) to the desired direction
  // CW-CCW pin controls the rotation direction of the motor. 
  // When set to H, the current of OUT_A is output first, with a phase difference of 90°. 
  // When set to L, the current of OUT_B is output first with a phase difference of 90°
  if(direction == true)
  {
    pinMode(stepper.settings.mode3Pin, INPUT); // let on-board external pullup to 3.3V pull this pin HIGH
  }
  else{
    pinMode(stepper.settings.mode3Pin, OUTPUT);
    digitalWrite(stepper.settings.mode3Pin, LOW);
  }

  // step the motor the desired amount of steps
  // each up-edge of the CLK signal (aka mode2Pin) 
  // will shift the motor's electrical angle per step.
  pinMode(stepper.settings.mode2Pin, OUTPUT);
  digitalWrite(stepper.settings.mode2Pin, LOW);
  delayMicroseconds(1); // even out the clock signal, error check takes about 2uSec
  delayMicroseconds(20); // was just a normal delay of 2ms, I think this was suboptimal??
  pinMode(stepper.settings.mode2Pin, INPUT); // let on-board external pullup to 3.3V pull this pin HIGH
  // check for error
  if(stepper.errorStat() == false) return false; // error detected, exit out of here!
  delayMicroseconds(20); // was delay
  return stepper.errorStat();
}

void Rail::move_absolute(double pos){
  // double dist_mm = pos - rail_position_;
  // Serial.print("Moving rail: ");
  // Serial.println(dist_mm);
  // int dist_steps = std::floor(dist_mm * get_step_per_mm());
  // Serial.print("Commanding this many steps: ");
  // Serial.println(dist_steps);
  // is_moving_ = true;
  // auto ret = stepper.step(abs(dist_steps) , std::signbit(dist_steps));
  // Serial.print("Moved completed successfully?: ");
  // Serial.println(ret);
  // is_moving_ = false;
  // rail_position_ = pos;
  job_queue_.push(Goal(pos));
}

void Rail::move_relative(double pos){
  /*
  Serial.print("Moving rail relative: ");
  Serial.print(pos);
  Serial.print("mm from: ");
  Serial.println(rail_position_);
  */
  move_absolute(rail_position_ + pos);
}

bool Rail::is_home_switch_hit(){
  return digitalRead(HOMING_PIN);
}