from voltageTest import VoltageTest

def connectSignals(ui):
    ui.pushButton_2.clicked.connect(lambda: VoltageTest.testVoltage(ui))
   # ui.pushButton.clicked.connect(Process.openServerSubProcess)