#!/usr/bin/python3

#import serial
#ser = serial.Serial('/dev/ttyUSB0', 9600)

# Communication with the arduino board

import os
import platform
import sys
import tty
import time
import threading
import termios
import camera as C
import pygame
import binascii
import serial
import numpy as np
import math

# Initialization of the connection to the Arduino
# board via usb
ser = serial.Serial('/dev/ttyUSB0', 115200)

#import joystick as J
import joystickTest as J

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
        #self.camera = C.Camera()
        self.windowWidth = 900
        self.windowHeight = 560
        pygame.init()
        surface = pygame.display.set_mode((self.windowWidth,
                                           self.windowHeight))
        pygame.display.set_caption('Pygame PS3 Demo')
        self.joystick = J.PS3_Controller(surface)
        self.leftWheelSpeed = 0
        self.rightWheelSpeed = 0
        self.rawDirection = None
        self.rawSpeed = None
        self.forward = 1
        self.angle = 0
        self.maxAngle = 25


    def Communication(self):
        ser.write("<" + str(int(self.leftWheelSpeed)) + \
                        str(int(self.rightWheelSpeed)) + ">")
        time.sleep(0.1)


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
                    for i in range(5, 1000):
                        ser.write(i)
                        time.sleep(20)
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

    def ComputeWheelsSpeed(self):
        if self.rawSpeed is not None:
            self.speed = (self.rawSpeed + 1.0) * 49.0
            assert(self.speed < 100.0)
        if self.rawDirection is not None:
            self.rawDirection[1] = - self.rawDirection[1]
            rawAngle = math.atan2(self.rawDirection[1], self.rawDirection[0]) * 180 / math.pi
            #print("Raw angle : " + str(rawAngle))
            if rawAngle == 0.0:
                # Idle left axis
                self.angle = 0.0
            else:
                if rawAngle < 0:
                    self.forward = 1
                else:
                    self.forward = 0
                rawAngle -= 90.0
                rawAngle /= 3
                if np.abs(rawAngle) > self.maxAngle:
                    self.angle = (self.maxAngle, -self.maxAngle)[rawAngle > 0]
                else:
                    self.angle = rawAngle
            #print("Computed angle : " + str(self.angle))
            if self.angle > 0.0:
                #Turn left
                self.leftWheelSpeed = self.speed - self.angle
                self.rightWheelSpeed = self.speed
            else:
                # turn right
                self.rightWheelSpeed = self.speed - self.angle
                self.leftWheelSpeed = self.speed
            #print(("Left / Right wheels speed : " + str(self.leftWheelSpeed) +
            #                            " - " + str(self.rightWheelSpeed)))
        else:
            print(self.rawDirection)

    def Start(self):

        #t1 = threading.Thread(target=self.GetKey)
        #t2 = threading.Thread(target=self.camera.run())
        #t3 = threading.Thread(target=self.Communication)

        #t1.start()
        #t2.start()
        #t3.start()

        while self.running is True:
            self.rawDirection, self.rawSpeed, self.running = self.joystick.run()
            self.ComputeWheelsSpeed()
            self.Communication()

        #self.camera.run()

        #t1.join()
        #t2.join()
        #t3.join()


if __name__ == "__main__":

    controller = Controller()

    controller.Start()

    print(" Termination")

