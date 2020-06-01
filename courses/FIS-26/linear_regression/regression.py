# coding: utf-8
import numpy as np
import csv
import datetime
import matplotlib.dates as mdates
import matplotlib.pyplot as plt


class OrdinaryLeastSquaresRegression:
    """
    This regression model is implemented for data analysis of the covid pandemic data.
    Basically, this model will be able to, using data achieved online in a csv sheet, determine how many
    days is necessary to the initial phase of the pandemy to be over.
    Some assumptions are made to achieved this result:
    A initial phase can be modeled by the equation: y = y0.exp(bt) where t is the time in days.
    To adjusts this data, we use the linear form: ln(y) = ln(y0) + b.t
    So, after trying to adjust the data, we check for outliers and remove the quantity of days that optimize
    R² and CHI².
    """

    def __init__(self, y: list, x: list, year, month, day, city):
        """
        Constructor.

        @param y: number of infecteds. (y[i] means y[i] infecteds in the day i since the first case)
        @@type y: list
        @param x: x axis values
        @@type x: list
        @param year: the year of the case 0
        @@type year: string        
        @param month: the month of the case 0
        @@type month: string        
        @param day: the day of the case 0
        @@type day: string
        @param city: city that provided the data
        @@type city: string
        """
        self.year = year
        self.month = month
        self.day = day

        self.city = city

        self.Y = np.log(np.array(y))
        self.X = np.array(x)

        self.r2_list = []

    def run(self):
        """
        This method will try to maximize the determination coefficient in the regression method.
        This way, will be possible to get the quantity of days necessary to be out of the initial pandemy growth.
        It's worth mentioning that we will avoid creating overfitting on the data by deleting too much data.
        This means we have to have at least 10 samples.
        """
        deleted = 0
        n = len(self.Y)
        while deleted < n and n - deleted > 10:
            # Get data
            observed = np.delete(self.Y, range(n - deleted, n))
            x = np.delete(self.X, range(n - deleted, n))

            # Adjust data
            ones_column_s = np.ones(len(observed), dtype=np.float64)
            adjusted_x = np.column_stack((ones_column_s, x))

            # Fit data
            _, fitted = self.fit(observed, adjusted_x)

            # Calculate the r2
            r2 = self.r2(fitted, observed)
            # Save it
            self.r2_list.append(r2)
            deleted += 1

        r2 = 0
        outlier = 0

        for i, r in enumerate(self.r2_list):
            if r > r2:
                r2 = r
                outlier = i
        
        # Getting result 
        observed = np.delete(self.Y, range(n - outlier, n))
        x = np.delete(self.X, range(n - outlier, n))
        ones_column_s = np.ones(len(observed), dtype=np.float64)
        adjusted_x = np.column_stack((ones_column_s, x))
        b, fitted = self.fit(observed, adjusted_x)

        # Plot adjusted data
        fitted_for_estimation = np.append(fitted, [b[0] + b[1] * self.X[i] for i in range(n - outlier, n)])
        self.plot_results(fitted_for_estimation, observed)
        # Calculate the time
        self.generate_results(fitted, observed, adjusted_x, b)

    def r2(self, fitted: list, observed: list) -> float:
        """
        Determination coefficient.

        @return r: the coefficient
        @@@type r: float
        """
        Y = observed
        Yf = fitted
        n = len(Y)

        Ym = np.array([np.mean(Y) for i in range(n)])

        sqtot = np.sum(np.dot((Y-Ym).T, Y-Ym))
        sqres = np.sum(np.dot((Y-Yf).T, Y-Yf))

        r2 = 1 - sqres / sqtot

        return r2

    def fit(self, observed, x):
        """
        Fit the data using the ordinary regression.

        @param observed: the observed data
        @@type observed: string
        @param x: the variable correlated with observed data (x axis)
        @@type x: string

        @return B: the parameters of the linear regression f(x) = B[0] + B[1] * x
        @@@type B: list
        @return Yf: the fitted data
        @@@type Yf: list
        """
        Y = observed
        X = x

        B = np.linalg.tensorsolve(np.matmul(X.T, X), np.matmul(X.T, Y.T))
        Yf = np.matmul(X, B)

        return B, Yf

    def plot_results(self, fitted_y, observed_y):
        """
        Plots the graph number of cases x days since the first one.
        Also, will plot the adjusted data and estimation if the pandemy followed the same rule since the beginning.

        @param fitted_y: fitted log of the number of cases in the regression.
        @@type fitted_y: list
        @param observed_y: number of cases observed
        @@type observed_y: list
        """
        d_time = np.array([xx for xx in self.X if xx], dtype=np.int64)

        tempDate = datetime.datetime(self.year, self.month, self.day)
        dates_t = (tempDate + d_time * datetime.timedelta(days=1))

        # Adjust datetime
        months = mdates.MonthLocator()  # every month
        weeks = mdates.WeekdayLocator()  # every week
        days = mdates.DayLocator()  # every day
        month_fmt = mdates.DateFormatter('%d/%b')  # day month

        _, ax = plt.subplots()
        plt.title(
            u'Ajuste log(Casos notificados) x tempo (dias). Cidade: ' + self.city)
        plt.plot(dates_t, self.Y, 'o')
        plt.plot(dates_t, fitted_y, '-')
        ax.xaxis.set_major_locator(weeks)
        ax.xaxis.set_minor_locator(days)
        ax.xaxis.set_major_formatter(month_fmt)
        plt.xlabel(u'tempo(dias)')
        plt.ylabel(u'log(Notificação)')

        plt.show()

    def generate_results(self, observed_y, fitted_y, adjusted_x, b):
        """
        Calculates the time for doubling the number of cases in the initial phase and the duration of this phase.

        @param fitted_y: fitted log of the number of cases in the regression.
        @@type fitted_y: list
        @param observed_y: number of cases observed
        @@type observed_y: list
        @param adjusted_x: days
        @@type adjusted_x: list
        @param b: parameters of the regression
        @@type b: list
        """
        # Estimate data variance using chi squared
        chi2 = np.dot(fitted_y - observed_y, fitted_y - observed_y)
        ngl = len(observed_y) - 2
        var = chi2 / ngl


        # Getting covariance matrix
        M_cov = var * np.linalg.inv(np.matmul(adjusted_x.T, adjusted_x))

        # Calcula t_doubling e sua incerteza
        t_doubling = np.log(2) / b[1]
        s_t_doubling = (np.log(2) / np.square(b[1])) * np.sqrt(M_cov[1, 1])

        print(u'%s / Tempo de doubling = %.2f dias / Incerteza = %.2f dias' %
              (self.city, t_doubling, s_t_doubling))
        print(u'%s / Tempo para sair do surto inicial: %d dias' %
              (self.city, len(adjusted_x)))
