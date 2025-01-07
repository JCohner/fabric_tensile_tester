#include <string>
#include "Arduino.h" // Serial

#include "robot.h"

void Robot::setup(){
  rail_.setup();
}

void Robot::tick_rail(){
  rail_.tick();
}

void Robot::tick(){
  // Update command_ if we are ready
  if (status_.get() != Status::RUNNING){
    if (!command_queue_.empty()){
      Serial.print("Grabbing new command: ");
      command_.set(command_queue_.front());
      Serial.println((int) command_.get()); // can probably use command map here
      command_queue_.pop();
    } else {
      command_.set(Command::NONE);
    }
  }

  // Switch based on current command, return status of that command
  auto status = Status::NONE;
  switch (command_.get()){
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
  switch (home_state_.get()){
    case HomeState::NOT_HOMED:
      Serial.println("We aren't homed! Commence homing");
      home_state_.set(HomeState::HOMING);
      break;
    case HomeState::HOMED:
      Serial.println("Already homed!!");
      status_.set(Status::SUCCESS);
      return; // no work left, EARLY RETURN
      break;
  }

  status_.set(Status::RUNNING);
  if (rail_.is_home_switch_hit()){
    Serial.println("Got home!");
    home_state_.set(HomeState::HOMED);
    status_.set(Status::SUCCESS);
    return;
  }

  // lame, move back 0.1mm...
  rail_.move_relative(0.1);

  // could put timeout here
}

void Robot::tick_preload(){
  // check is_homed()
  status_.set(Status::RUNNING);
  switch (preload_state_.get()){
    case PreloadState::PRELOADED:
      Serial.println("Already preloaded but new value requested");
    case PreloadState::NOT_PRELOADING:
      Serial.println("Waiting for preload value");
      preload_state_.set(PreloadState::PRELOAD_GETTING_VALUE); // INCREMENT STATE
    case PreloadState::PRELOAD_GETTING_VALUE:
      // don't spam, just wait for value patiently
      if (target_position_.check_edge()){
        Serial.print("Got preload pos value: ");
        Serial.println(target_position_.get());
        preload_state_.set(PreloadState::PRE_LOAD_MOVING_TO_VALUE); // INCREMENT STATE
      }
    break;
    case PreloadState::PRE_LOAD_MOVING_TO_VALUE:
      rail_.move_absolute(target_position_.get());
      Serial.println("Moved to position!");
      preload_state_.set(PreloadState::PRELOADED);
      status_.set(Status::SUCCESS);
      break;
  }

}

void Robot::enqueue_message(arduino::String incoming_string){
    if (incoming_string == "q"){
      Serial.println("Resetting robot state");
      status_.set(Status::NONE);
      // probably clear queue and such
    }

    // if we are currently fielding PRELOADING command
  if (command_.get() == Command::PRELOAD && preload_state_.get() == PreloadState::PRELOAD_GETTING_VALUE){
    auto val_to_go_to = atoi(incoming_string.c_str()); // uninterp strings return 0, this is actuall bad for us
    Serial.print("Command new preload target:  ");
    Serial.println(val_to_go_to);
    target_position_.set(val_to_go_to);
  }
  else { // otherwise just interpret whatever incoming string to just be a command
    auto command_enum = command_map[incoming_string.c_str()]; // invalid keys will be enum = 0 == NONE
    if (command_enum != Command::NONE){
      enqueue_command(command_enum);
    }
  }
}