#!/usr/bin/python3

#import serial
#ser = serial.Serial('/dev/ttyACM0', 9600)

# Communication with the arduino board

import os
import platform
import sys,tty
import time
import threading
import termios

import serial

ser = serial.Serial('/dev/ttyACM0',9600)

class _Getch:
    def __init__(self):
        pass
    def getKey(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(3)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            return ch

def PrintOSData():
    print(os.name)
    print(platform.system())
    print(platform.release())

class Controller():
    def __init__(self):
        PrintOSData()
        self.running = True
        self.keyboardWatcher = _Getch()
        self.printLock = threading.Lock()

    def Communication(self):
        pass

    def ParallelFunction(self):
        while(self.running):
            print("..")
            time.sleep(1)
        print("Exit ParallelFunction")

    def GetKey(self):
        while (self.running):
            if os.name == "posix" :
                print("key?")
                while(1):
                    k=self.keyboardWatcher.getKey()
                    if k!='':break
                if k=='\x1b[A':
                    print("up")
                    ser.write('1')
                elif k=='\x1b[B':
                    print("down")
                    ser.write('2')
                elif k=='\x1b[C':
                    print("right")
                    ser.write('3')
                elif k=='\x1b[D':
                    print("left")
                    ser.write('4')
                elif k=='\x1b':
                    print("alert")
                else:
                    print("not an arrow key! : " + str(k))
                    self.running = False
                    sys.exit(0)
                    print("on le voit pas")

            elif platform.system() == "Darwin":
                print("in")
                tty.setcbreak(sys.stdin)
                key = ord(sys.stdin.read(1))  # key captures the key-code
                if key==97:
                    print("you pressed a")
                if key=='\x1b[A':
                    print("up")
                else:
                    print("you pressed" + str(key))

    def Start(self):
        
        t1 = threading.Thread(target=self.GetKey)
        t2 = threading.Thread(target=self.ParallelFunction)
        
        t1.start()
        t2.start()
        
        t1.join()
        t2.join()

if __name__ == "__main__":

    controller = Controller()

    controller.Start()

    print(" Termination")

