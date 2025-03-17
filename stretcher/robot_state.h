#ifndef __ROBOT_STATE_H__
#define __ROBOT_STATE_H__

#include <avr/dtostrf.h>
#include <sstream>

struct RobotState {
  RobotState()
    : target_position_(0)
    , home_state_(HomeState::NOT_HOMED)
    , preload_state_(PreloadState::NOT_PRELOADING)
    , test_state_ (TestState::NOT_TESTING)
    , command_ (Command::NONE)
    , status_ (Status::NONE){
  }
  stateful_member<double> target_position_ {0};
  stateful_member<double> current_position_ {0};
  stateful_member<double> current_load_ {0};
  stateful_member<HomeState> home_state_;
  stateful_member<PreloadState> preload_state_;
  stateful_member<TestState> test_state_;
  stateful_member<Command> command_; // the robot executes commands, in doing so it will permutate robot state variables
  stateful_member<Status> status_;


  void serialize(char* buff){
    char current_position_float_string[10] = {0};
    char current_target_float_string[10] = {0};
    char current_load_float_string[10] = {0};
    dtostrf(current_position_.get(), 4, 2, current_position_float_string);
    dtostrf(target_position_.get(), 4, 2, current_target_float_string);
    dtostrf(current_load_.get(), 4, 2, current_load_float_string);
    sprintf(buff, "hs: %d, ps: %d, ts: %d, c: %d, s: %d, ct:  %s, cp: %s, cl:%s\r",
            home_state_.get_int(), 
            preload_state_.get_int(), 
            test_state_.get_int(), 
            command_.get_int(), status_.get_int(), 
            current_target_float_string, 
            current_position_float_string, 
            current_load_float_string);
  }
};

#endif /* __ROBOT_STATE_H__ */