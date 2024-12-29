#include <map>
#include <string>

#include <Arduino.h>

#include "robot.h"
#include "user_interface.h"

std::map<arduino::String, Robot::Command> command_map = {
  {"home", Robot::Command::HOME},
  {"pre", Robot::Command::PRELOAD},
  {"test", Robot::Command::TEST}
};

Robot::Command check_for_commands(){
  char buff[50]; 
  int i = 0;
  Robot::Command command_enum = Robot::Command::NONE;
  if (Serial.available() > 0){
    auto incoming_string = Serial.readStringUntil('\r');
    Serial.print("Reading command: ");
    Serial.println(incoming_string);
    auto command_enum = command_map[incoming_string.c_str()]; // invalid keys will be enum = 0 == NONE 
  }
  return command_enum;
}
