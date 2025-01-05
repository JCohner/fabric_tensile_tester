#ifndef __HELPER_H__
#define __HELPER_H__

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

#endif /* __HELPER_H__ */