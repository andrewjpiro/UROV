# -*- coding: utf-8 -*-

import socket
import json
from sfml.window import Joystick as j
import time
from PyQt4.QtCore import QObject, pyqtSignal, pyqtSlot
import random

def readAxis(axis):
    """Takes axis as an argument (4 axis- X, Y, Z and R), and returns the value at that instance."""
    #Note: TECHNICALLY 6 axis - there is also a U and V axis
    if isConnected():
        return j.get_axis_position(0, j.__getattribute__(j, axis)) #this is lazy and may not work; TEST!
    else:
        pass
    
def readButton(button):
    """Takes a button value (buttons 1-8) and returns whether or not it is pushed."""
    if isConnected():
        return j.is_button_pressed(0, button)
    else:
        pass
    
def isConnected():
    """Returns True if joystick is connected."""
    return j.is_connected(0)
    

def process2DAxis(l, h):
    """Processes the lateral and horizontal axis of a joystick, to be used as inputs
    for a motor controller."""
    Ellipsis
    
    

def encapsulateData(fp = "write.txt", **kwargs):
    """Encapsulates all kwargs in their key:value pairs, returns a JSON object.
    Objects to be encapsulated: ALL OF THEM (Axis X-V, Buttons 1-10."""
    fp = open(fp, "w")
    json.dump(kwargs, fp, indent = 4, sort_keys = True)
    
    
#    
#BUFSIZE = 4096    #reasonably sized buffer for data
###---Socket/TCP-IP Code occurs here ---**
#def send(data = str):
#    conn.send(data.encode())
#def recieve():
#    recieve.data = conn.recv(BUFSIZE)
#    recieve.data = recieve.data.decode()
#    return recieve.data

##---Socket/TCP-IP Code ends here ---**

class Server(QObject):

    x = pyqtSignal(int)
    count = 0
    def __init__(self):
        # self.host = socket.gethostbyname(socket.gethostname())
        # print "HOST: ", self.host
        # self.port = 1900
        # self.address = (self.host, self.port)
        # self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # self.server.bind((self.address))
        # self.server.listen(1)
        # print "Looking for Client to talk to...."
        # self.conn, self.address = self.server.accept()
        # output = self.conn.recv(2048)
        # print "Message received from client:"
        # print output
        # self.count = 0

        self.y = pyqtSignal(int)
        self.z = pyqtSignal(int)
        self.u = pyqtSignal(int)
        self.r = pyqtSignal(int)
        self.v = pyqtSignal(int)
        super(Server, self).__init__()
        print "FINISHED INITIALIZING"


    def update(self):
        #count += 1 #we'll print the x, y, z, r values every 5 runs through program
        try:
        #     j.update()
        #     self.y.emit(readAxis('Y') * -4)
        #     y = readAxis('Y') * -4
            print "EMITTING X"
            #x_val = readAxis("X") * -4
            x_val = random.randint(0, 100)
            self.x.emit(x_val)
        #     self.z.emit(readAxis('Z') * -4)
        #     z = readAxis('Z') * -4
        #     self.u.emit(readAxis('U') * -4)
        #     u = readAxis('U') * -4
        #     self.r.emit(readAxis('R') * -4)
        #     r = readAxis('R') * -4
        #     self.v.emit(readAxis('V') * -4)
        #     v = readAxis('Z') * -4
        #     b1 = readButton(1)
        #     b2 = readButton(2)
        #     b3 = readButton(3)
        #     b4 = readButton(4)
        #     b5 = readButton(5)
        #     b6 = readButton(6)
        #     b7 = readButton(7)
        #     b8 = readButton(8)
        #     b9 = readButton(9)
        #     b10 = readButton(10)
        #     self.conn.send("{\"X\":%d,\"Y\":%d,\"Z\":%d,\"R\":%d}~"%(x, y, z, r))
        #     time.sleep(0.1)
        except socket.error as error:
            print "ERROR CAUGHT."
            self.server.listen(1)
            print "Looking for Client to talk to...."
            conn, address = self.server.accept()
        # if self.count % 5 == 0:
        #     print "{\"X\":%d,\"Y\":%d,\"Z\":%d,\"R\":%d} "%(x, y, z, r)



if __name__ == '__main__':
    server = Server()
    server.update()
        
        
    
