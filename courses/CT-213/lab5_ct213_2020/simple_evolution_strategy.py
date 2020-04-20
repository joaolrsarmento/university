import numpy as np


class SimpleEvolutionStrategy:
    """
    Represents a simple evolution strategy optimization algorithm.
    The mean and covariance of a gaussian distribution are evolved at each generation.
    """

    def __init__(self, m0, C0, mu, population_size):
        """
        Constructs the simple evolution strategy algorithm.

        :param m0: initial mean of the gaussian distribution.
        :type m0: numpy array of floats.
        :param C0: initial covariance of the gaussian distribution.
        :type C0: numpy matrix of floats.
        :param mu: number of parents used to evolve the distribution.
        :type mu: int.
        :param population_size: number of samples at each generation.
        :type population_size: int.
        """
        self.m = m0
        self.C = C0
        self.mu = mu
        self.population_size = population_size
        self.samples = np.random.multivariate_normal(
            self.m, self.C, self.population_size)

    def ask(self):
        """
        Obtains the samples of this generation to be evaluated.
        The returned matrix has dimension (population_size, n), where n is the problem dimension.

        :return: samples to be evaluated.
        :rtype: numpy array of floats.
        """
        return self.samples

    def tell(self, fitnesses):
        """
        Tells the algorithm the evaluated fitnesses. The order of the fitnesses in this array
        must respect the order of the samples.

        :param fitnesses: array containing the value of fitness of each sample.
        :type fitnesses: numpy array of floats.
        """
        # Sort the samples based on its fitness.
        # Basically, given two arrays A = (a1,a2,a3,a4) and B = (b1,b2,b3,b4):
        # We zip them together: zip(A,B) = ((a1,b1), (a2,b2), (a3,b3), (a4,b4))
        # And, them, sort the array using the second parameter (its fitness) as comparator
        self.samples = [x for x, _ in sorted(zip(self.samples, fitnesses),
                                             key=lambda x: x[1])]
        # Here, we select the best mu samples
        parents = self.samples[0:self.mu]
        # Transform it into a numpy matrix
        matrix = np.matrix(parents)
        # Tranpose the matrix
        transpose = matrix.transpose()
        # Calculate the covariance of this best samples by a method implement by me
        self.C = self.covariance(parents)
        # Get the new mean with the new best samples
        self.m = np.mean(transpose, axis=1)
        # Format it into a vector
        self.m = self.m.A1
        # Generate new samples around the new mean using the new covariance matrix
        self.samples = np.random.multivariate_normal(
            self.m, self.C, self.population_size)

    def covariance(self, parents):
        """
        Makes the matrix multiplication between vectors and its transpost to calculate
        the covariance matrix.

        :param parents: matrix with vectors
        :type parents: numpy matrix

        :return covariance: covariance matrix
        :type covariance: numpy matrix
        """
        # Transform the mean into a matrix with mu rows and n columns
        mean_matrix = np.matrix(np.array([self.m for i in range(self.mu)]))
        # Makes the matrix multiplication between the matrix and its tranpost
        covariance = np.matrix(np.dot((parents - mean_matrix).T,
                                       parents - mean_matrix))
        # Normalize it, assuming we know the mean
        covariance = covariance / self.mu

        return covariance
