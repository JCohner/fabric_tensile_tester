import serial

class SerialInterface():
  def __init__(self):
    self.default_port = "/dev/ttyACM0"
    self.ser = serial.Serial()
    self.is_connected = False
  def open(self, port: str):
    self.ser.baudrate = 9600
    self.ser.port = port
    self.ser.open() # determine how and if to catch error
    self.is_connected = True
  def close(self):
    self.ser.close()
    self.is_connected = False
