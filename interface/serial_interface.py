import serial
from multiprocessing import Value
from threading import Thread
from queue import Queue
from ctypes import c_bool
import time


class SerialInterface():
  def __init__(self):
    self.default_port = "/dev/ttyACM0"
    self.ser = serial.Serial()
    self.is_connected = Value(c_bool, False)

    self.is_working = Value(c_bool, False)
    self.message_queue = Queue()
    self.work_thread = Thread(target=self.serial_interface_workthread)


  def open(self, port: str):
    self.ser.baudrate = 9600
    self.ser.port = port
    self.ser.open() # determine how and if to catch error
    self.is_connected.value = True
  
  def close(self):
    self.ser.close()
    self.is_connected.value = False


  def serial_interface_workthread(self):
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
          print(f"message read as {mess}")
          self.message_queue.put(mess)

  def start_work(self):
    if (not self.is_working.value):
      self.is_working.value = True
      self.work_thread.start()

  def stop_work(self):
    if (self.is_working.value):
      self.is_working.value = False
      self.work_thread.join()