#include <string>

#include "robot.h"
#include "Arduino.h"

void Robot::setup(){
  rail_.setup();
}

Robot::Update Robot::tick(){
  // Get new command if 
  if (current_command_status_ != Robot::Status::RUNNING){
    if (!command_queue_.empty()){
      Serial.print("Grabbing new command: ");
      current_command_ = command_queue_.front();
      Serial.println((int) current_command_);
      command_queue_.pop();
    } else {
      current_command_ = Robot::Command::NONE;
    }
    //Serial.print("New command: "); Serial.println(current_command_);
  }

  Robot::Status status = Robot::Status::NONE;
  switch (current_command_){
    case Robot::Command::HOME:
      status = tick_home();
      break;
    case Robot::Command::PRELOAD:
      //status = tick_preload();
      break;
    case Robot::Command::TEST:
      //status = tick_test();
      break;
  }

  current_command_status_ = status;
  return Robot::Update(current_command_, status);
}

Robot::Status Robot::tick_home(){
  Serial.println("Checking that home shit");
  if (rail_.is_home_switch_hit()){
    Serial.println("Got it bitch");
    return Robot::Status::SUCCESS;
  }
  // lame, move back 0.1mm...
  rail_.move_relative(0.1);
  return Robot::Status::RUNNING;
}