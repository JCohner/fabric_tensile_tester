from PyQt6.QtWidgets import QMainWindow, QApplication
from qt_app_schema import Ui_MainWindow

from threading import Thread

from worker import Worker
from serial_interface import SerialInterface
from state_interactor import StateInteractor

class StretchEmUI(QMainWindow, Worker):
   def __init__(self):
      super(StretchEmUI, self).__init__()

      # Set up the user interface from Designer.
      self.ui = Ui_MainWindow()
      self.ui.setupUi(self)

      # connect serial up
      self.serial = SerialInterface()
      self.serial.start_work()

      # start state interactor
      self.state_interactor = StateInteractor(self.serial.message_queue)
      self.state_interactor.start_work() 

      self.start_work()

      ''' 
      Wire up buttons
      '''
      # Serial buttons
      self.ui.connectSerialButton.clicked.connect(self.attempt_serial_connect)
      self.ui.disconnectSerialButton.clicked.connect(self.attempt_serial_disconnect)
      # Control buttons
      self.ui.homeButton.clicked.connect(self.attempt_home)

   def attempt_serial_connect(self):
      if (self.ui.serialPortLineEdit.isModified()):
         port_name = self.ui.serialPortLineEdit.text()
         if (port_name[:-1] != "/dev/ttyACM"):
            print("doesn't look right champ try again")
            return
      else:
         print("Using default serial port: /dev/ttyACM0")
         port_name = "/dev/ttyACM0"
      print(f"Opening serial on: {port_name}")
      self.serial.open(port_name)
      self.ui.isSerialConnectedIndicator.setStyleSheet("background-color: green")

   def attempt_serial_disconnect(self):
      print(f"Disconnecting from {self.serial.ser.port}")
      self.serial.close()
      self.ui.isSerialConnectedIndicator.setStyleSheet("background-color: red")

   def attempt_home(self):
      if (not self.serial.is_connected.value):
         print("Not connected to serial, not sending command")

   def work_thread(self):
      while(self.is_working.value):
         if (not self.state_interactor.state_update_queue.empty()):
            val = self.state_interactor.state_update_queue.get()
            print(val)

            # we have val!! we can now interact with it graphically inshallah

   def __del__(self):
      print("closing shit")
      self.serial.stop_work()
      self.serial.close()
      self.state_interactor.stop_work() 


def main():
   import sys
   app = QApplication(sys.argv)
   MainWindow = StretchEmUI()

   MainWindow.show()
   print("GOT HERE")
   sys.exit(app.exec())


if __name__ == '__main__':
   main()