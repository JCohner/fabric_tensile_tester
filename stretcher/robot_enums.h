#ifndef __ROBOT_ENUMS_H__
#define __ROBOT_ENUMS_H__

/*
Management of robot state. 
*/

enum struct HomeState {
  NOT_HOMED = 0,
  HOMING = 1,
  HOMED = 2
};

enum struct PreloadState {
  NOT_PRELOADING = 0,
  PRELOAD_GETTING_VALUE = 1,
  PRE_LOAD_MOVING_TO_VALUE = 2,
  PRELOADED = 3
};

enum struct TestState {
  NOT_TESTING = 0,
  TESTING = 1,
  TEST_COMPLETED = 2 
};

#endif /* __ROBOT_ENUMS_H__ */