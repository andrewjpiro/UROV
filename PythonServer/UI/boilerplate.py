__author__ = 'Aaron'

import sys

from PyQt4 import QtGui, QtCore
from Generated.generatedGUI import  Ui_MainWindow

from connection import connectSignals

class Example(QtGui.QMainWindow):
    def __init__(self):
        super(Example, self).__init__()

        self.initUI()

    def initUI(self):

        self.statusBar().showMessage('Ready')
        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('Statusbar')
        self.show()

def main():

    app = QtGui.QApplication(sys.argv)
    ui = Ui_MainWindow()
    ex = Example()
    ui.setupUi(ex)

    connectSignals(ui)

    sys.exit(app.exec_())


if __name__ == '__main__':
    main()