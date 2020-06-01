# coding: utf-8
import numpy as np
import csv
import datetime
import matplotlib.dates as mdates
import matplotlib.pyplot as plt
from linear_regression import regression

CHOSEN_CITIES = ['Rio de Janeiro', 'Sao Luis', 'Belo Horizonte']

for city in CHOSEN_CITIES:

    input_data_file = 'database/data/' + city + '.csv'
    input_init_file = 'database/data/Init_' + city + '.txt'
    Y = np.array([], dtype=np.float64)
    X = np.array([], dtype=np.float64)

    # Leitura da data da primeira notificação
    file_init = open(input_init_file, 'r')
    line = file_init.readlines()
    temp = line[0].split()
    day = np.int(temp[1])
    temp = line[1].split()
    month = np.int(temp[1])
    temp = line[2].split()
    year = np.int(temp[1])
    file_init.close()

    with open(input_data_file, 'r') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=',')

        next(spamreader, None)
        for row in spamreader:
            Y = np.append(Y, np.float(row[0]))
            X = np.append(X, np.float(row[1]))


    # RUN MODEL
    
    model = regression.OrdinaryLeastSquaresRegression(Y, X, year, month, day, city)
    model.run()

