from PyQt4 import QtCore

class VoltageTest(QtCore.QObject):

    @staticmethod
    def testVoltage(ui):
        ui.lcdNumber.display(71)
