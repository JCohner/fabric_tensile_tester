#ifndef __STEPPER_H__
#define __STEPPER_H__

#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" 


class Stepper {
public:
  Stepper() {

  }
  void setup();
  void move()
private:
  PRODRIVER myProDriver;
  double position = 0;
};


#endif