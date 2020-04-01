from math import exp
import random


def simulated_annealing(cost_function, random_neighbor, schedule, theta0, epsilon, max_iterations):
    """
    Executes the Simulated Annealing (SA) algorithm to minimize (optimize) a cost function.

    :param cost_function: function to be minimized.
    :type cost_function: function.
    :param random_neighbor: function which returns a random neighbor of a given point.
    :type random_neighbor: numpy.array.
    :param schedule: function which computes the temperature schedule.
    :type schedule: function.
    :param theta0: initial guess.
    :type theta0: numpy.array.
    :param epsilon: used to stop the optimization if the current cost is less than epsilon.
    :type epsilon: float.
    :param max_iterations: maximum number of iterations.
    :type max_iterations: int.
    :return theta: local minimum.
    :rtype theta: np.array.
    :return history: history of points visited by the algorithm.
    :rtype history: list of np.array.
    """
    # First guess
    theta = theta0
    history = [theta0]
    # Number of iterations
    num_iterations = 0
    # This boolean will check if the variable theta has changed.
    # This is done to avoid store the same variable in the history.
    changed = False
    # Check stopping condition
    while cost_function(theta) >= epsilon and num_iterations < max_iterations:
        # Get temperature that is decreasing
        T = schedule(num_iterations)
        num_iterations += 1
        # This won't happen
        if T < 0:
            return theta
        # Get random neighbor
        neighbor = random_neighbor(theta)
        # Check difference
        deltaE = cost_function(neighbor) - cost_function(theta)
        # If the cost decreased, we have a new theta
        if deltaE <= 0:
            changed = True
            theta = neighbor
        else:
            r = random.uniform(0.0, 1.0)
            # If this random number if less than the probabily, we have a new theta
            # Avoids local minimum
            if r < exp(-deltaE / T):
                changed = True
                theta = neighbor
        # If we have a new theta, store it
        if changed:
            # Stores this theta
            history.append(theta)
        changed = False
    return theta, history
