#ifndef __RAIL_H__
#define __RAIL_H__

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" 

class Rail {
public:
  Rail() {

  }
  void setup();
  void move_absolute(double pos);
  void move_relative(double pos);
  double get_position() {return rail_position_;}
  bool is_moving(){ return is_moving_;}
  bool is_home_switch_hit();
private:
  PRODRIVER stepper;
  const int HOMING_PIN = 14;
  void setup_stepper(void);
  double rail_position_ = 0;
  const double rail_pitch_ = 2.0;
  const double base_step_per_rev = 200.0;
  double get_step_per_mm();
  volatile bool is_moving_ = false;
};


#endif /*__RAIL_H__*/