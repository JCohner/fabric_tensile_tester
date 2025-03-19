from threading import Thread
from multiprocessing import Value
from ctypes import c_bool


class Worker():
  def __init__(self):
    self.work_thread = Thread(target=self.work_thread)
    self.is_working = Value(c_bool, False)

  def start_work(self):
    if (not self.is_working.value):
      self.is_working.value = True
      self.work_thread.start()

  def stop_work(self):
    if (self.is_working.value):
      self.is_working.value = False
      self.work_thread.join()

  def work_thread(self):
    raise NotImplementedError("Need to override base class work_thread")