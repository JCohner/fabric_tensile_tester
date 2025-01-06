#ifndef __ROBOT_COMMANDS_H__
#define __ROBOT_COMMANDS_H__

#include <map>
#include <string>

/*

  Enumeration of fieldable commands and response status robot 
  responds upon ticking in current state

*/ 
enum struct Command {
  NONE = 0,
  HOME = 1,
  PRELOAD = 2,
  TEST = 3,
  CLEAR_QUEUE = 4
};

// mechanism to serialize commands
static std::map<std::string, Command> command_map = {
  {"home", Command::HOME},
  {"pre", Command::PRELOAD},
  {"test", Command::TEST}
};

#endif /* __ROBOT_COMMANDS_H__ */