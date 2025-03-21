from dataclasses import dataclass
from enum import Enum, StrEnum, IntEnum
from queue import Queue
import time

from worker import Worker

# must be kept inline with stretcher/robot_enums.h
class HomeState(Enum):
  NOT_HOMED = 0
  HOMING = 1
  HOMED = 2

class PreloadState(Enum):
  NOT_PRELOADING = 0
  PRELOAD_GETTING_VALUE = 1
  PRE_LOAD_MOVING_TO_VALUE = 2
  PRELOADED = 3

class TestState(Enum):
  NOT_TESTING = 0
  TESTING = 1
  TEST_COMPLETED = 2

# must be kept inline with stretcher/robot_commands.h
class CommandIn(IntEnum):
  NONE = 0
  HOME = 1,
  PRELOAD = 2,
  TEST = 3,
  CLEAR_QUEUE = 4,


class CommandOut(StrEnum):
  HOME = "home\r",
  PRELOAD = "pre\r",
  TEST = "test\r",
  CLEAR_QUEUE = "q\r",


# must be kept inline with stretcher/status.h
class Status(Enum):
  NONE = 0
  RUNNING = 1
  SUCCESS = 2
  FAILURE = 3

@dataclass
class State():
  home_state: HomeState = HomeState.NOT_HOMED
  preload_state: PreloadState = PreloadState.NOT_PRELOADING
  test_state: TestState = TestState.NOT_TESTING
  command: CommandIn = CommandIn.NONE
  status: Status = Status.NONE
  current_target: float = 0
  current_position: float = 0
  current_load: float = 0


class StateInteractor(Worker):
  def __init__(self, serial_message_queue):
    super().__init__()
    self.message_queue = serial_message_queue
    self.state_update_queue = Queue()

  # Work thread consuming serial port ouput and synthesizing state messages
  def work_thread(self):
    while(self.is_working.value):
      time.sleep(0.01) # prevent fighting on the queue
      if (not self.message_queue.empty()):
        message = self.message_queue.get()
        dm = {sub[0] : float(sub[1]) for sub in (el.split(":") for el in message.split(","))} # cursed
        state_update = State(home_state=HomeState(dm['hs']),
                             preload_state=PreloadState(dm['ps']),
                             test_state=TestState(dm['ts']),
                             command=CommandIn(dm['c']),
                             status=Status(dm['s']),
                             current_target=dm['ct'],
                             current_position=dm['cp'],
                             current_load=dm['cl'])
        self.state_update_queue.put(state_update)
        # print(self.state_update_queue.qsize())
