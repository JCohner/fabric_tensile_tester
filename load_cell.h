#ifndef __LOAD_CELL_H__
#define __LOAD_CELL_H__

#include <functional>
#include <queue>

class LoadCell {
public:
  void tick() {
    auto val = read_load_cell();
    if (num_samples <= WINDOW) num_samples++;
    value_ = (val + (old_value_ * (((double) num_samples) - 1.0))) / ((double) num_samples);
    old_value_ = value_;
  }
  double get_value() { return value_;}
private:
  const int WINDOW = 250; // at a 2ms rate this is a 500ms window
  int num_samples = 0;
  double value_ = 0;
  double old_value_ = 0;
  int load_cell_pin = A7;
  std::function<int(void)> read_load_cell = [this](){return analogRead(this->load_cell_pin);};
};

#endif /* __LOAD_CELL_H__ */