#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <queue>

#include "rail.h"

class Robot {
public:
  enum struct Command {
    NONE = 0,
    HOME = 1,
    PRELOAD = 2,
    TEST = 3,
    CLEAR_QUEUE = 4
  };
  enum struct Status {
    NONE = 0,
    RUNNING = 1,
    SUCCESS = 2,
    FAILURE = 3
  };
  struct Update {
    Update(Command com, Status stat): command(com), status(stat) {} 
    Command command;
    Status status;
  };

  void enqueue_command(Command command) {command_queue_.push(command);}
  Update tick();

private:
  // Peripherals
  Rail rail_;

  // Command Centric Guys
  std::queue<Command> command_queue_;
  Command current_command_;
  Status current_command_status_;
  Status tick_home();
  Status tick_preload();
  Status tick_test();
};


#endif /*__ROBOT_H__*/