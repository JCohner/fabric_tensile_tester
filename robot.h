#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <queue>
#include <string>
#include <functional>

#include <Arduino.h>

#include "helper.h"

#include "rail.h"

#include "status.h"
#include "robot_enums.h"
#include "robot_commands.h"

class Robot {
public:
  void enqueue_message(arduino::String incoming_string);
  void tick_rail();
  void tick();
  void setup();
  Robot() 
    : target_position_(0)
    , home_state_(HomeState::NOT_HOMED)
    , preload_state_(PreloadState::NOT_PRELOADING)
    , test_state_ (TestState::NOT_TESTING)
    , command_ (Command::NONE)
    , status_ (Status::NONE)
  {}

private:
  // Peripherals
  Rail rail_;

  // State management
  stateful_member<double> target_position_ {0};
  stateful_member<HomeState> home_state_;
  stateful_member<PreloadState> preload_state_;
  stateful_member<TestState> test_state_;
  stateful_member<Command> command_; // the robot executes commands, in doing so it will permutate robot state variables
  stateful_member<Status> status_;

  // load cell things
  int load_cell_pin = A7;
  std::function<int(void)> read_load_cell = [this](){return analogRead(this->load_cell_pin);};

  // Command Centric Guys
  void enqueue_command(Command command) {command_queue_.push(command);}
  std::queue<Command> command_queue_;
  
  void tick_home();
  void tick_preload();
  void tick_test();
};


#endif /*__ROBOT_H__*/