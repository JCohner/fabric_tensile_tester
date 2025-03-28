import serial
from queue import Queue
import time
from multiprocessing import Value
from ctypes import c_bool

from worker import Worker

class SerialInterface(Worker):
  def __init__(self):
    super().__init__()
    self.default_port = "/dev/ttyACM0"
    self.ser = serial.Serial()
    self.is_connected = Value(c_bool, False)

    # out queue
    self.message_queue = Queue()
    # in queue
    self.command_queue = Queue()


  def open(self, port: str):
    self.ser.baudrate = 9600
    self.ser.port = port
    self.ser.open() # determine how and if to catch error
    self.is_connected.value = True
  
  def close(self):
    self.ser.close()
    self.is_connected.value = False


  def work_thread(self):
    char_buff = []
    while(self.is_working.value):
      time.sleep(0.5)
      # only meaningful if we are connected
      while (self.is_connected.value):
        val = self.ser.read()
        char_buff.append(val.decode("utf-8"))
        if val == b'\r':
          mess = ''.join(char_buff)
          char_buff = []
          self.message_queue.put(mess)
          # print(f"{self.ser.in_waiting}") # good debug for making sure we are conusming all inbound messages

        if (not self.command_queue.empty()):
          command = self.command_queue.get()
          print(f"writing value: {command}")
          self.ser.write(command)
