# -*- coding: utf-8 -*-

import socket
import json
from sfml.window import Joystick as j
import time


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

    
if __name__ == "__main__":
    host = socket.gethostbyname(socket.gethostname())
    print "HOST: ", host
    port = 1900
    address = (host, port)
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((address))
    server.listen(1)
    print "Looking for Client to talk to...."
    conn, address = server.accept()
    output = conn.recv(2048)
    print "Message received from client:"
    print output



    #TODO: Realize that this code immediately raises an error if there is no server to connect to
    count = 0
    while True:
        count += 1 #we'll print the x, y, z, r values every 5 runs through program
        try:
            j.update()
            y = readAxis('Y') * -4
            x = readAxis("X") * -4
            z = readAxis('Z') * -4
            u = readAxis('U') * -4
            r = readAxis('R') * -4
            v = readAxis('Z') * -4
            b1 = readButton(1)
            b2 = readButton(2)
            b3 = readButton(3)
            b4 = readButton(4)
            b5 = readButton(5)
            b6 = readButton(6)
            b7 = readButton(7)
            b8 = readButton(8)
            b9 = readButton(9)
            b10 = readButton(10)
        
            conn.send("{\"X\":%d,\"Y\":%d,\"Z\":%d,\"R\":%d}~"%(x, y, z, r))
            
#            print '''
#            y: %s
#            x: %s
#            z: %s
#            u: %s
#            r: %s
#            v: %s
#            '''%(y, x, z, u, r, v)
            time.sleep(0.1)
        except socket.error as error:
            print "ERROR CAUGHT."
            server.listen(1)
            print "Looking for Client to talk to...."
            conn, address = server.accept()
        if count % 5 == 0:
            print "{\"X\":%d,\"Y\":%d,\"Z\":%d,\"R\":%d} "%(x, y, z, r)
        
        
        
        
    
