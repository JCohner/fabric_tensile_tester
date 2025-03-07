#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <queue>
#include <string>

#include <Arduino.h>

#include "helper.h"

#include "rail.h"
#include "load_cell.h"

#include "status.h"
#include "robot_enums.h"
#include "robot_commands.h"
#include "robot_state.h"

class Robot {
public:
  void enqueue_message(arduino::String incoming_string);
  void tick_rail() {rail_.tick();};
  void tick_load_cell() {load_cell_.tick();};
  void tick();
  void setup();
  void post_update(char* mess) {
    state_.serialize(mess);
  }
  Robot() {}

private:
  // Peripherals
  Rail rail_;

  // State management
  RobotState state_;

  // load cell things
  LoadCell load_cell_;

  // Command Centric Guys
  void enqueue_command(Command command) {command_queue_.push(command);}
  std::queue<Command> command_queue_;
  
  void tick_home();
  void tick_preload();
  void tick_test();
};


#endif /*__ROBOT_H__*/