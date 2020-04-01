from math import inf
import numpy as np

def hill_climbing(cost_function, neighbors, theta0, epsilon, max_iterations):
    """
    Executes the Hill Climbing (HC) algorithm to minimize (optimize) a cost function.

    :param cost_function: function to be minimized.
    :type cost_function: function.
    :param neighbors: function which returns the neighbors of a given point.
    :type neighbors: list of numpy.array.
    :param theta0: initial guess.
    :type theta0: numpy.array.
    :param epsilon: used to stop the optimization if the current cost is less than epsilon.
    :type epsilon: float.
    :param max_iterations: maximum number of iterations.
    :type max_iterations: int.
    :return theta: local minimum.
    :rtype theta: numpy.array.
    :return history: history of points visited by the algorithm.
    :rtype history: list of numpy.array.
    """
    # First guess
    theta = theta0
    history = [theta0]
    # Number of iterations
    num_iterations = 0
    # Check stopping condition
    while cost_function(theta) >= epsilon and num_iterations < max_iterations:
        num_iterations += 1
        # Starts the array best with None
        best = np.array([None] * len(theta))
        for neighbor in neighbors(theta):
            # Checks if the best is None (is this the first attempt?) or 
            # the neighbor is better than best
            if np.all(best == None) or cost_function(neighbor) < cost_function(best):
                best = neighbor
        # If there isn't a neighbor better than theta, return the answer
        if cost_function(theta) < cost_function(best):
            return theta, history
        # Now, we should test the best
        theta = best
        # Stores this new theta
        history.append(theta)
    return theta, history
