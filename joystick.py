#!/usr/bin/python
import pygame
import os
import time
import usb
import cv2

os.environ['SDL_VIDEO_CENTERED'] = '1'

if not pygame.joystick.get_init():
            pygame.joystick.init()

if not pygame.display.get_init():
    pygame.display.init()

if not pygame.font.get_init():
    pygame.font.init()

if not pygame.mixer.get_init():
    pygame.mixer.init()

if not pygame.joystick.get_init():
    pygame.joystick.init()

class Joystick(object):

    def __init__(self):
        self.joystick = None
        self.t = 0
        self.time = time.time
        self.direction = None #
        self.speed = None     #[-1;1] to [0;100]
        self.running = 1

    def check_status(self):
        pygame.event.pump()
        if self.t == 0:
            print "Connected"
            self.t = 1
            pygame.joystick.quit()
            pygame.joystick.init()
            joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
            while len(joysticks) <= 0:
                pygame.joystick.quit()
                pygame.joystick.init()
                joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
            for joystick in joysticks:
                if 'playstation' in joystick.get_name().lower():
                    print joystick.get_name()
                    self.joystick = joystick
                    self.joystick.init()

    def run(self):
        pygame.init()
        self.check_status()
        print(self.joystick)
        while (self.running):
            if (self.joystick is not None):
                self.speed = (self.joystick.get_axis(13) + 1) * 50
                print("Speed : " + str(self.joystick.get_axis(13)))
                self.direction = [self.joystick.get_axis(0),
                                  self.joystick.get_axis(1)]
            else:
                print("PB;")
