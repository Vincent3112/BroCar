import math

class Odometry(object):

    def __init__(self, vehicleLength):
        self.x = 0
        self.y = 0
        self.theta = 0
        self.v = 0
        self.vehicleLength = vehicleLength


    def update(self, delta_t, epsilon, a):
        self.x += self.v * delta_t * math.cos(self.theta)
        self.y += self.v * delta_t * math.sin(self.theta)
        self.theta += (self.v / self.vehicleLength) * epsilon * delta_t
        self.v += a * delta_t

