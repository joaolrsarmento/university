def gradient_descent(cost_function, gradient_function, theta0, alpha, epsilon, max_iterations):
    """
    Executes the Gradient Descent (GD) algorithm to minimize (optimize) a cost function.

    :param cost_function: function to be minimized.
    :type cost_function: function.
    :param gradient_function: gradient of the cost function.
    :type gradient_function: function.
    :param theta0: initial guess.
    :type theta0: numpy.array.
    :param alpha: learning rate.
    :type alpha: float.
    :param epsilon: used to stop the optimization if the current cost is less than epsilon.
    :type epsilon: float.
    :param max_iterations: maximum number of iterations.
    :type max_iterations: int.
    :return theta: local minimum.
    :rtype theta: numpy.array.
    :return history: history of points visited by the algorithm.
    :rtype history: list of numpy.array.
    """
    # First variable to be tested
    theta = theta0
    # Array to store the path to get to the minimum
    history = [theta0]
    # Number of iterations
    num_interations = 0
    # Stopping condition:
    # The cost_function should be less than epsilon and also the num of iterations should be 
    # less than max_iterations.
    while cost_function(theta) >= epsilon and num_interations < max_iterations:
        # Increases the num of iterations
        num_interations += 1
        # Get new theta
        theta = theta - alpha * gradient_function(theta)
        # Save this theta
        history.append(theta)
    return theta, history
