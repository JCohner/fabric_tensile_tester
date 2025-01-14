#ifndef __HELPER_H__
#define __HELPER_H__

/*
  Slightly poorly named but I have found the below
  class useful for member variables, especially when 
  I want to catch an edge of such variable. This explicit
  get and set is nice. 

  Weird TODO: I have found you can directly assign a V_TYPE value to the class itself
  this probably has to do with default assignment operator.... 
*/

template <typename V_TYPE>
struct stateful_member {
private:
  V_TYPE val;
  V_TYPE prev_val;

public:
  stateful_member(V_TYPE init_val){
    val = init_val;
    prev_val = (V_TYPE)0; // could be helpful
  }
  void set(V_TYPE new_val) { 
    prev_val = val;
    val = new_val;
  }
  V_TYPE get() {return val;}

  bool check_edge() {
    auto ret_val = val != prev_val;
    prev_val = val; // .checking edge, updates or notion of last state so the edge will no longer remain
    return ret_val;
  }
  // Check specific edge, do not increment if no match
  bool check_edge(V_TYPE specific_previous_val) {
    if (prev_val != specific_previous_val) return false;
    auto ret_val = val != prev_val;
    prev_val = val; // .checking edge, updates or notion of last state so the edge will no longer remain
    return ret_val;
  }
};

#include <cmath>

// float comparison helper
static bool floatCompare(double f1, double f2, double thresh = 0) {
  return std::fabs(f1 - f2) <= (1.0e-5 * std::fmax(std::fabs(f1), std::fabs(f2)) + thresh); 
}

#endif /* __HELPER_H__ */