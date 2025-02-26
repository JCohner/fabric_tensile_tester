#ifndef __ROBOT_STATE_H__
#define __ROBOT_STATE_H__

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
  stateful_member<HomeState> home_state_;
  stateful_member<PreloadState> preload_state_;
  stateful_member<TestState> test_state_;
  stateful_member<Command> command_; // the robot executes commands, in doing so it will permutate robot state variables
  stateful_member<Status> status_;

};

#endif /* __ROBOT_STATE_H__ */