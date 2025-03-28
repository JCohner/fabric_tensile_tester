# Form implementation generated from reading ui file 'app.ui'
#
# Created by: PyQt6 UI code generator 6.4.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(835, 600)
        MainWindow.setStyleSheet("QPushButton#pushButton_4 {\n"
"    background-color: red;\n"
"    border-width: 2px;\n"
"    border-color: beige;\n"
"}")
        self.centralwidget = QtWidgets.QWidget(parent=MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.controlGroupBox = QtWidgets.QGroupBox(parent=self.centralwidget)
        self.controlGroupBox.setGeometry(QtCore.QRect(20, 30, 331, 301))
        self.controlGroupBox.setObjectName("controlGroupBox")
        self.homeButton = QtWidgets.QPushButton(parent=self.controlGroupBox)
        self.homeButton.setGeometry(QtCore.QRect(10, 40, 87, 26))
        self.homeButton.setObjectName("homeButton")
        self.preloadButton = QtWidgets.QPushButton(parent=self.controlGroupBox)
        self.preloadButton.setGeometry(QtCore.QRect(10, 100, 87, 26))
        self.preloadButton.setObjectName("preloadButton")
        self.testButton = QtWidgets.QPushButton(parent=self.controlGroupBox)
        self.testButton.setGeometry(QtCore.QRect(10, 150, 87, 26))
        self.testButton.setObjectName("testButton")
        self.isHomedLabel = QtWidgets.QLabel(parent=self.controlGroupBox)
        self.isHomedLabel.setGeometry(QtCore.QRect(180, 50, 66, 18))
        self.isHomedLabel.setObjectName("isHomedLabel")
        self.stopButton = QtWidgets.QPushButton(parent=self.controlGroupBox)
        self.stopButton.setGeometry(QtCore.QRect(220, 150, 87, 26))
        self.stopButton.setAcceptDrops(False)
        self.stopButton.setStyleSheet("QPushButton#pushButton_4 {\n"
"    background-color: red;\n"
"    border-width: 2px;\n"
"    border-color: beige;\n"
"}")
        self.stopButton.setObjectName("stopButton")
        self.preloadDistanceLineEdit = QtWidgets.QLineEdit(parent=self.controlGroupBox)
        self.preloadDistanceLineEdit.setGeometry(QtCore.QRect(150, 100, 161, 26))
        self.preloadDistanceLineEdit.setObjectName("preloadDistanceLineEdit")
        self.currentPosLabel = QtWidgets.QLabel(parent=self.controlGroupBox)
        self.currentPosLabel.setGeometry(QtCore.QRect(20, 200, 151, 20))
        self.currentPosLabel.setObjectName("currentPosLabel")
        self.currentPosValueLabel = QtWidgets.QLabel(parent=self.controlGroupBox)
        self.currentPosValueLabel.setGeometry(QtCore.QRect(190, 200, 66, 18))
        self.currentPosValueLabel.setObjectName("currentPosValueLabel")
        self.currentLoadLabel = QtWidgets.QLabel(parent=self.controlGroupBox)
        self.currentLoadLabel.setGeometry(QtCore.QRect(20, 230, 151, 20))
        self.currentLoadLabel.setObjectName("currentLoadLabel")
        self.currentLoadValueLabel = QtWidgets.QLabel(parent=self.controlGroupBox)
        self.currentLoadValueLabel.setGeometry(QtCore.QRect(190, 230, 66, 18))
        self.currentLoadValueLabel.setObjectName("currentLoadValueLabel")
        self.isHomedIndicatorLabel = QtWidgets.QLabel(parent=self.controlGroupBox)
        self.isHomedIndicatorLabel.setGeometry(QtCore.QRect(250, 50, 66, 18))
        self.isHomedIndicatorLabel.setStyleSheet("QLabel#isHomedIndicatorLabel{\n"
" background-color: red;\n"
"}")
        self.isHomedIndicatorLabel.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.isHomedIndicatorLabel.setObjectName("isHomedIndicatorLabel")
        self.serialConnectionGroupBox = QtWidgets.QGroupBox(parent=self.centralwidget)
        self.serialConnectionGroupBox.setGeometry(QtCore.QRect(20, 370, 351, 151))
        self.serialConnectionGroupBox.setObjectName("serialConnectionGroupBox")
        self.connectSerialButton = QtWidgets.QPushButton(parent=self.serialConnectionGroupBox)
        self.connectSerialButton.setGeometry(QtCore.QRect(10, 40, 87, 26))
        self.connectSerialButton.setObjectName("connectSerialButton")
        self.isSerialConnectedLabel = QtWidgets.QLabel(parent=self.serialConnectionGroupBox)
        self.isSerialConnectedLabel.setGeometry(QtCore.QRect(20, 110, 111, 18))
        self.isSerialConnectedLabel.setObjectName("isSerialConnectedLabel")
        self.isSerialConnectedIndicator = QtWidgets.QGraphicsView(parent=self.serialConnectionGroupBox)
        self.isSerialConnectedIndicator.setGeometry(QtCore.QRect(120, 100, 31, 31))
        self.isSerialConnectedIndicator.setAutoFillBackground(True)
        self.isSerialConnectedIndicator.setStyleSheet("QGraphicsView#isSerialConnectedIndicator {\n"
"    background-color: red;\n"
"}")
        brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
        brush.setStyle(QtCore.Qt.BrushStyle.NoBrush)
        self.isSerialConnectedIndicator.setBackgroundBrush(brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))
        brush.setStyle(QtCore.Qt.BrushStyle.NoBrush)
        self.isSerialConnectedIndicator.setForegroundBrush(brush)
        self.isSerialConnectedIndicator.setObjectName("isSerialConnectedIndicator")
        self.serialPortLineEdit = QtWidgets.QLineEdit(parent=self.serialConnectionGroupBox)
        self.serialPortLineEdit.setGeometry(QtCore.QRect(140, 40, 141, 26))
        self.serialPortLineEdit.setObjectName("serialPortLineEdit")
        self.disconnectSerialButton = QtWidgets.QPushButton(parent=self.serialConnectionGroupBox)
        self.disconnectSerialButton.setGeometry(QtCore.QRect(10, 70, 87, 26))
        self.disconnectSerialButton.setObjectName("disconnectSerialButton")
        self.loadCellCalibrationGroupBox = QtWidgets.QGroupBox(parent=self.centralwidget)
        self.loadCellCalibrationGroupBox.setGeometry(QtCore.QRect(440, 30, 271, 211))
        self.loadCellCalibrationGroupBox.setObjectName("loadCellCalibrationGroupBox")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(parent=MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 835, 23))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(parent=MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.controlGroupBox.setTitle(_translate("MainWindow", "Control Buttons"))
        self.homeButton.setText(_translate("MainWindow", "Home"))
        self.preloadButton.setText(_translate("MainWindow", "Preload"))
        self.testButton.setText(_translate("MainWindow", "Test"))
        self.isHomedLabel.setText(_translate("MainWindow", "Homed?"))
        self.stopButton.setText(_translate("MainWindow", "STOP"))
        self.preloadDistanceLineEdit.setPlaceholderText(_translate("MainWindow", "preload distance (mm)"))
        self.currentPosLabel.setText(_translate("MainWindow", "Current Position(mm):"))
        self.currentPosValueLabel.setText(_translate("MainWindow", "NA"))
        self.currentLoadLabel.setText(_translate("MainWindow", "Current Load(no unit):"))
        self.currentLoadValueLabel.setText(_translate("MainWindow", "NA"))
        self.isHomedIndicatorLabel.setText(_translate("MainWindow", "No"))
        self.serialConnectionGroupBox.setTitle(_translate("MainWindow", "Serial Connection"))
        self.connectSerialButton.setText(_translate("MainWindow", "Connect"))
        self.isSerialConnectedLabel.setText(_translate("MainWindow", "Is Conneted?"))
        self.serialPortLineEdit.setPlaceholderText(_translate("MainWindow", "ex: /dev/ttyACM0"))
        self.disconnectSerialButton.setText(_translate("MainWindow", "Disconnect"))
        self.loadCellCalibrationGroupBox.setTitle(_translate("MainWindow", "Load Cell Calibration"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec())
