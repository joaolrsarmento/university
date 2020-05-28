import pygame
import math
import numpy as np
from utils import FRAME_TIME, GRAVITY, BLACK, WHITE, RED, BLUE, GREEN, SCREEN_WIDTH, SCREEN_HEIGHT, RECT_PARAMETERS, PIVOT, PI


class DampedPendulum:
    def __init__(self, L, M, maximumAngle, b, c):
        """
        This class represents a pendulum in a enviroment where its motion equations include damping.
        The class also saves the theta position for plotting proposes.

        @param L: length of the rope in meters
        @@ type L: float
        @param M: mass of the ball in kilograms
        @@ type M: float
        @param maximumAngle: initial amplitude in radians
        @@ type maximumAngle: float
        @param b: constant in the linear damping
        @@ type b: float
        @param c: constant in the quadratic damping
        @@ type c: float
        """
        self.x = np.array([math.sin(maximumAngle), math.cos(maximumAngle)]) * L # Ball position
        self.v = 0 # Speed
        self.a = 0 # Acceleration
        self.g = GRAVITY # Gravity

        self.maximumAngle = maximumAngle # Initial amplitude
        self.theta = maximumAngle # Updated angular position

        self.L = L
        self.M = M
        self.b = b
        self.c = c

        self.history = [[], []] # Saves time and angular position for plotting
        self.time = 0 # time step

        pygame.init()
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("Damped Pendulum")
        self.screen.fill(WHITE)
        pygame.display.update()

    def update(self):
        """
        Update kinematic values: acceleration, speed, angular position, time

        @return history: history of the simulation
        @@type history: list of lists
        """
        self.history[0].append(self.time) # Saving time
        self.history[1].append(self.theta) # Saving angular position
        self.a = self.getAcceleration() # Getting acceleration
        self.v = self.v + self.a * FRAME_TIME # Updating speed
        self.theta = self.theta - (self.v / self.L) * FRAME_TIME # Updating angular position
        self.time = self.time + FRAME_TIME # Updating time step
        self.move() # Updating cartesian position

        return self.history

    def move(self):
        """
        Update cartesian position.

        """
        self.x = np.array(
            [math.sin(self.theta), math.cos(self.theta)]) * self.L

    def draw(self):
        """
        Draw pendulum elements like rope, sphere and ceiling.

        """
        position = np.array(PIVOT) + np.array((int(self.x[0]), int(self.x[1])))
        pygame.draw.rect(self.screen, BLACK, RECT_PARAMETERS)
        pygame.draw.circle(self.screen, RED, position, 12)
        pygame.draw.line(self.screen, BLACK, PIVOT, position, 1)

    def getAcceleration(self):
        """
        Newton's second law for the pendulum.
        Here, we use this equation: a (in v direction) = g sin(theta) - b.v - c.v.|v|, considering the damping.

        @return a: updated acceleration due angular position variation.
        @@type a: float
        """
        a = self.g * math.sin(self.theta) - (self.b *
                                             self.v + self.c * np.abs(self.v) * self.v) / self.M
        return a

