from tensorflow.keras import layers, activations
from tensorflow.keras.models import Sequential


def make_lenet5():

    model = Sequential()

    model.add(layers.Conv2D(6, kernel_size=(5, 5), strides=(1, 1), activation='tanh', input_shape=(32, 32, 1)))

    model.add(layers.AveragePooling2D(pool_size=(2, 2), strides=(2, 2)))

    model.add(layers.Conv2D(16, kernel_size=(5, 5), strides=(1, 1), activation='tanh'))

    model.add(layers.AveragePooling2D(pool_size=(2, 2), strides=(2, 2)))

    model.add(layers.Conv2D(120, kernel_size=(5, 5), strides=(1, 1), activation='tanh'))

    model.add(layers.Flatten())

    model.add(layers.Dense(84, activation='tanh'))

    model.add(layers.Dense(10, activation='softmax'))

    return model
