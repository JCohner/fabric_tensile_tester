#include <string>
#include "Arduino.h" // Serial

#include "robot.h"

void Robot::setup(){
  rail_.setup();
  load_cell_.setup();
}

void Robot::tick(){
  // values to update every tick
  state_.current_position_.set(rail_.get_position());
  state_.current_load_.set(load_cell_.get_value());

  // Update command_ if we are ready
  if (state_.status_.get() != Status::RUNNING){
    if (!command_queue_.empty()){
      Serial1.print("Grabbing new command: ");
      state_.command_.set(command_queue_.front());
      Serial1.println((int) state_.command_.get()); // can probably use command map here
      command_queue_.pop();
    } else {
      state_.command_.set(Command::NONE);
    }
  }

  // Switch based on current command, return status of that command
  auto status = Status::NONE;
  switch (state_.command_.get()){
    case Command::HOME:
      tick_home();
      break;
    case Command::PRELOAD:
      tick_preload();
      break;
    case Command::TEST:
      //tick_test();
      break;
  }
}

void Robot::tick_home(){
  // first check if we are already homed
  switch (state_.home_state_.get()){
    case HomeState::NOT_HOMED:
      Serial1.println("We aren't homed! Commence homing");
      state_.home_state_.set(HomeState::HOMING);
      break;
    case HomeState::HOMED:
      Serial1.println("Already homed!!");
      state_.status_.set(Status::SUCCESS);
      return; // no work left, EARLY RETURN
      break;
  }

  state_.status_.set(Status::RUNNING);
  if (rail_.is_home_switch_hit()){
    Serial1.println("Got home!");
    state_.home_state_.set(HomeState::HOMED);
    state_.status_.set(Status::SUCCESS);
    return;
  }

  // lame, move back 0.1mm...
  rail_.move_relative(0.1);

  // could put timeout here
}

void Robot::tick_preload(){
  // check is_homed()
  state_.status_.set(Status::RUNNING);
  switch (state_.preload_state_.get()){
    case PreloadState::PRELOADED:
      Serial1.println("Already preloaded but new value requested");
    case PreloadState::NOT_PRELOADING:
      Serial1.println("Waiting for preload value");
      state_.preload_state_.set(PreloadState::PRELOAD_GETTING_VALUE); // INCREMENT STATE
    case PreloadState::PRELOAD_GETTING_VALUE:
      // don't spam, just wait for value patiently
      if (state_.target_position_.check_edge()){
        Serial1.print("Got preload pos value: ");
        Serial1.println(state_.target_position_.get());
        state_.preload_state_.set(PreloadState::PRE_LOAD_MOVING_TO_VALUE); // INCREMENT STATE
        rail_.move_absolute(state_.target_position_.get());
      }
    break;
    case PreloadState::PRE_LOAD_MOVING_TO_VALUE:
      char buff[100] = {0};
      sprintf(buff, "Load Cell: %06.1f\t Current pos: %.2f vs Goal Pos %.2f\r", load_cell_.get_value(),rail_.get_position(),state_.target_position_.get());
      Serial1.print(buff);
      if (rail_.job_complete()){
        Serial1.print("\n");
        Serial1.println("Preload move done");
        state_.preload_state_.set(PreloadState::PRELOADED);
        state_.status_.set(Status::SUCCESS);
      }
      break;
  }

}

void Robot::enqueue_message(char* buff, int len){
    std::string incoming_string = std::string(buff);
    incoming_string.pop_back();
    
    if (incoming_string == "q"){
      Serial1.println("Resetting robot state");
      state_.status_.set(Status::NONE);
      // probably clear queue and such
      state_.home_state_.set(HomeState::NOT_HOMED);
      state_.preload_state_.set(PreloadState::NOT_PRELOADING);
    }

    // if we are currently fielding PRELOADING command
  if (state_.command_.get() == Command::PRELOAD && state_.preload_state_.get() == PreloadState::PRELOAD_GETTING_VALUE){
    auto val_to_go_to = atoi(incoming_string.c_str()); // uninterp strings return 0, this is actuall bad for us
    Serial1.print("Command new preload target:  ");
    Serial1.println(val_to_go_to);
    state_.target_position_.set(val_to_go_to);
  }
  else { // otherwise just interpret whatever incoming string to just be a command
    auto command_enum = command_map[incoming_string.c_str()]; // invalid keys will be enum = 0 == NONE
    if (command_enum != Command::NONE){
      enqueue_command(command_enum);
    }
  }
}