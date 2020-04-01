import random
import math
from constants import *


class FiniteStateMachine(object):
    """
    A finite state machine.
    """
    def __init__(self, state):
        self.state = state

    def change_state(self, new_state):
        self.state = new_state

    def update(self, agent):
        self.state.check_transition(agent, self)
        self.state.execute(agent)


class State(object):
    """
    Abstract state class.
    """
    def __init__(self, state_name):
        """
        Creates a state.

        :param state_name: the name of the state.
        :type state_name: str
        """
        self.state_name = state_name

    def check_transition(self, agent, fsm):
        """
        Checks conditions and execute a state transition if needed.

        :param agent: the agent where this state is being executed on.
        :param fsm: finite state machine associated to this state.
        """
        raise NotImplementedError("This method is abstract and must be implemented in derived classes")

    def execute(self, agent):
        """
        Executes the state logic.

        :param agent: the agent where this state is being executed on.
        """
        raise NotImplementedError("This method is abstract and must be implemented in derived classes")


class MoveForwardState(State):
    def __init__(self):
        super().__init__("MoveForward")

        self.linearSpeed = FORWARD_SPEED
        self.angularSpeed = 0

        self.executionTime = 0
        self.frameTime = SAMPLE_TIME
        self.totalTime = MOVE_FORWARD_TIME

    def check_transition(self, agent, state_machine):

        if agent.get_bumper_state():
            state_machine.change_state(GoBackState())
        if self.executionTime >= self.totalTime:
            state_machine.change_state(MoveInSpiralState())

    def execute(self, agent):
        self.executionTime += self.frameTime
        agent.set_velocity(self.linearSpeed, self.angularSpeed)

class MoveInSpiralState(State):
    def __init__(self):
        super().__init__("MoveInSpiral")

        self.initialRadius = INITIAL_RADIUS_SPIRAL
        self.radiusGrowth = SPIRAL_FACTOR

        self.linearSpeed = SPIRAL_LINEAR_SPEED
        self.angularSpeed = 0
    
        self.executionTime = 0
        self.frameTime = SAMPLE_TIME
        self.totalTime = MOVE_IN_SPIRAL_TIME

    def check_transition(self, agent, state_machine):
        if agent.get_bumper_state():
            state_machine.change_state(GoBackState())
        if self.executionTime >= self.totalTime:
            state_machine.change_state(MoveForwardState())

    def execute(self, agent):
        self.executionTime += self.frameTime
        self.radius = self.initialRadius + self.radiusGrowth * self.executionTime / self.frameTime
        self.angularSpeed = self.linearSpeed / self.radius

        agent.set_velocity(self.linearSpeed, self.angularSpeed)



class GoBackState(State):
    def __init__(self):
        super().__init__("GoBack")
        
        self.linearSpeed = BACKWARD_SPEED
        self.angularSpeed = 0

        self.executionTime = 0
        self.frameTime = SAMPLE_TIME
        self.totalTime = GO_BACK_TIME

    def check_transition(self, agent, state_machine):
        if self.executionTime >= self.totalTime:
            state_machine.change_state(RotateState())

    def execute(self, agent):
        self.executionTime += self.frameTime
        agent.set_velocity(self.linearSpeed, self.angularSpeed)

class RotateState(State):
    def __init__(self):
        super().__init__("Rotate")

        self.linearSpeed = 0
        self.angularSpeed = ANGULAR_SPEED

        self.executionTime = 0

        self.randomAngle = math.pi * random.random()

        self.totalTime = int(self.randomAngle / ANGULAR_SPEED)
        self.frameTime = SAMPLE_TIME

    def check_transition(self, agent, state_machine):
        if self.executionTime >= self.totalTime:
            state_machine.change_state(MoveForwardState())
    
    def execute(self, agent):
        self.executionTime += self.frameTime
        agent.set_velocity(self.linearSpeed, self.angularSpeed)

