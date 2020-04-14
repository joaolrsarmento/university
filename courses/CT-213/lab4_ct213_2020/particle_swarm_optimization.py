import numpy as np
import random
from math import inf


class Particle:
    """
    Represents a particle of the Particle Swarm Optimization algorithm.
    """

    def __init__(self, lower_bound, upper_bound):
        """
        Creates a particle of the Particle Swarm Optimization algorithm.

        :param lower_bound: lower bound of the particle position.
        :type lower_bound: numpy array.
        :param upper_bound: upper bound of the particle position.
        :type upper_bound: numpy array.
        """
        # Minimum position
        self.lower_bound = lower_bound
        # Maximum position
        self.upper_bound = upper_bound
        # Maximum velocity
        self.delta = upper_bound - lower_bound

        # Chooses initial position and velocity using a uniform distribution
        self.position = np.random.uniform(lower_bound, upper_bound)
        self.velocity = np.random.uniform(-self.delta, self.delta)

        # Stores the best value (maximum) found until now
        self.best_value = -inf
        # The position that corresponds to the value stored
        self.best_position = self.position


class ParticleSwarmOptimization:
    """
    Represents the Particle Swarm Optimization algorithm.
    Hyperparameters:
        inertia_weight: inertia weight.
        cognitive_parameter: cognitive parameter.
        social_parameter: social parameter.
        num_particles: number of particules when using the algorithm.

    :param hyperparams: hyperparameters used by Particle Swarm Optimization.
    :type hyperparams: Params.
    :param lower_bound: lower bound of particle position.
    :type lower_bound: numpy array.
    :param upper_bound: upper bound of particle position.
    :type upper_bound: numpy array.
    """

    def __init__(self, hyperparams, lower_bound, upper_bound):

        self.lower_bound = lower_bound
        self.upper_bound = upper_bound

        self.delta = upper_bound - lower_bound

        self.hyperparams = hyperparams

        # Initialize particles
        self.particles = [Particle(self.lower_bound, self.upper_bound)
                          for i in range(self.hyperparams.num_particles)]
        # This integer will store which particle (number from 0 to number of particles - 1)
        # is being analyzed
        self.particle_number = 0
        # Stores the position that corresponds to the best global value
        self.best_position = None
        # Best global value
        self.best_value = -inf

    def get_best_position(self):
        """
        Obtains the best position so far found by the algorithm.

        :return: the best position.
        :rtype: numpy array.
        """
        return self.best_position

    def get_best_value(self):
        """
        Obtains the value of the best position so far found by the algorithm.

        :return: value of the best position.
        :rtype: float.
        """

        return self.best_value

    def get_position_to_evaluate(self):
        """
        Obtains a new position to evaluate.

        :return: position to evaluate.
        :rtype: numpy array.
        """
        particle = self.particles[self.particle_number]
        # Get the position from the particle being analyzed
        return particle.position

    def advance_generation(self):
        """
        Advances the generation of particles.
        """
        phip = self.hyperparams.cognitive_parameter
        phig = self.hyperparams.social_parameter
        w = self.hyperparams.inertia_weight

        for particle in self.particles:
            rp = random.uniform(0.0, 1.0)
            rg = random.uniform(0.0, 1.0)
            v = particle.velocity

            # Get new velocity
            particle.velocity = w * particle.velocity + \
                phip * rp * (particle.best_position - particle.position) + \
                phig * rg * (self.best_position - particle.position)
            # Uses the heuristic function to put the velocity into a limit
            particle.velocity = np.minimum(np.maximum(-self.delta, particle.velocity),
                                           self.delta)
            # Get new position
            particle.position = particle.position + particle.velocity
            # Uses the heuristic function to put the velocity into a limit
            particle.position = np.minimum(np.maximum(self.lower_bound, particle.position),
                                           self.upper_bound)

    def notify_evaluation(self, value):
        """
        Notifies the algorithm that a particle position evaluation was completed.

        :param value: quality of the particle position.
        :type value: float.
        """
        particle = self.particles[self.particle_number]

        # Update the bests from the particle being analyzed
        if value > particle.best_value:
            particle.best_value = value
            particle.best_position = particle.position
        # Update best global
        if value > self.best_value:
            self.best_value = value
            self.best_position = particle.position
        # Go to the next particle
        self.particle_number += 1
        # Checks if a generation was completely analyzed
        if self.particle_number == self.hyperparams.num_particles:
            self.particle_number = 0
            self.advance_generation()
