#ifndef __RAIL_H__
#define __RAIL_H__

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" 

#include <queue>

#include "status.h"
#include "helper.h"

struct Goal {
  Goal (double pos)
    : position(pos)
    , status(Status::NONE)
  {}
  Goal()
    : position(0)
    , status(Status::NONE)
  {}
  double position;
  int steps_to_move = 0;
  bool direction = 0;
  int steps_moved = 0; // how many steps we've taken towards our goal
  stateful_member<Status> status;
};

class Rail {
public:
  Rail() {

  }
  void tick();
  void setup();
  double get_position() {return rail_position_;}
  void enqueue_move(double pos) {job_queue_.push(Goal(pos));}

  bool is_home_switch_hit();
  void move_absolute(double pos);
  void move_relative(double pos);

  bool job_complete() {return current_goal_.status.get() == Status::SUCCESS;}

private:
  // stepper driver 
  PRODRIVER stepper;
  const int HOMING_PIN = 14;
  void setup_stepper(void);
  
  // position management
  bool is_moving(){ return is_moving_;}
  bool non_blocking_step(bool direction);

  // Position state
  double rail_position_ = 0;
  volatile bool is_moving_ = false;
  
  // Lead screw factors
  const double rail_pitch_ = 2.0;
  const double base_step_per_rev = 200.0;
  //double get_step_per_mm();
  const double step_per_mm = stepper.settings.stepResolution * (1.0 / rail_pitch_) * base_step_per_rev;
  const double mm_per_step = 1.0 / step_per_mm;
  std::queue<Goal> job_queue_;
  Goal current_goal_;
};


#endif /*__RAIL_H__*/