#ifndef __LOAD_CELL_H__
#define __LOAD_CELL_H__

#include <queue>
#include <HX711.h>

class LoadCell {
public:
  void setup() {scale_.begin(load_cell_data, load_cell_clock);}
  void tick() {
    if (scale_.is_ready()){
      auto val = scale_.read();
      if (num_samples <= WINDOW) num_samples++;
      value_ = (val + (old_value_ * (((double) num_samples) - 1.0))) / ((double) num_samples);
      old_value_ = value_;
    }
  }
  double get_value() { return value_;}
private:
  HX711 scale_;
  const int WINDOW = 25; // at a 2ms rate this is a 500ms window
  int num_samples = 0;
  volatile double value_ = 0;
  double old_value_ = 0;
  int load_cell_data = 20;
  int load_cell_clock = 19;
};

#endif /* __LOAD_CELL_H__ */