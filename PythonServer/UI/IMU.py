__author__ = 'Aaron'

from PyQt4 import QtCore
from Generated.generatedGUI import  Ui_MainWindow

class IMU_Test(QtCore.QObject):
    def __init__(self, ui):
        self.ui = ui
        super(IMU_Test, self).__init__()

    @QtCore.pyqtSlot(float)
    def testAccel(self, accel):
        self.ui.lcdNumber_9.display(accel)

    @QtCore.pyqtSlot(float)
    def testGyro(self, gyro):
        self.ui.lcdNumber_10.display(gyro)

    @QtCore.pyqtSlot(float)
    def testCompass(self, compass):
        self.ui.lcdNumber_11.display(compass)

