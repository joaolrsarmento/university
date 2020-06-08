from tensorflow.keras.models import load_model
import cv2
import math as m
import numpy as np
from utils import sigmoid


class YoloDetector:
    """
    Represents an object detector for robot soccer based on the YOLO algorithm.
    """

    def __init__(self, model_name, anchor_box_ball=(5, 5), anchor_box_post=(2, 5)):
        """
        Constructs an object detector for robot soccer based on the YOLO algorithm.

        :param model_name: name of the neural network model which will be loaded.
        :type model_name: str.
        :param anchor_box_ball: dimensions of the anchor box used for the ball.
        :type anchor_box_ball: bidimensional tuple.
        :param anchor_box_post: dimensions of the anchor box used for the goal post.
        :type anchor_box_post: bidimensional tuple.
        """
        self.network = load_model(model_name + '.hdf5')
        self.network.summary()  # prints the neural network summary
        self.anchor_box_ball = anchor_box_ball
        self.anchor_box_post = anchor_box_post

    def detect(self, image):
        """
        Detects robot soccer's objects given the robot's camera image.

        :param image: image from the robot camera in 640x480 resolution and RGB color space.
        :type image: OpenCV's image.
        :return: (ball_detection, post1_detection, post2_detection), where each detection is given
                by a 5-dimensional tuple: (probability, x, y, width, height).
        :rtype: 3-dimensional tuple of 5-dimensional tuples.
        """
        image = self.preprocess_image(image)

        output = self.network.predict(image)

        ball_detection, post1_detection, post2_detection = self.process_yolo_output(
            output)

        return ball_detection, post1_detection, post2_detection

    def preprocess_image(self, image):
        """
        Preprocesses the camera image to adapt it to the neural network.

        :param image: image from the robot camera in 640x480 resolution and RGB color space.
        :type image: OpenCV's image.
        :return: image suitable for use in the neural network.
        :rtype: NumPy 4-dimensional array with dimensions (1, 120, 160, 3).
        """
        image = cv2.resize(image, (160, 120), interpolation=cv2.INTER_AREA)
        image = np.array(image)
        image = image / 255
        image = np.reshape(image, (1, 120, 160, 3))

        return image

    def process_yolo_output(self, output):
        """
        Processes the neural network's output to yield the detections.

        :param output: neural network's output.
        :type output: NumPy 4-dimensional array with dimensions (1, 15, 20, 10).
        :return: (ball_detection, post1_detection, post2_detection), where each detection is given
                by a 5-dimensional tuple: (probability, x, y, width, height).
        :rtype: 3-dimensional tuple of 5-dimensional tuples.
        """
        coord_scale = 4 * \
            8  # coordinate scale used for computing the x and y coordinates of the BB's center
        bb_scale = 640  # bounding box scale used for computing width and height
        # reshaping to remove the first dimension
        output = np.reshape(output, (15, 20, 10))
        
        coordinates_pb = self.get_coordinates_maximum(output[:, :, 0])
        coordinates_pp1 = self.get_coordinates_maximum(output[:, :, 5])
        coordinates_pp2 = self.get_coordinates_second_maximum(output[:, :, 5])

        ball_detection = (sigmoid(output[coordinates_pb[0], coordinates_pb[1], 0]),
                          (coordinates_pb[1] + sigmoid(output[coordinates_pb[0], coordinates_pb[1], 1])) * coord_scale,
                          (coordinates_pb[0] + sigmoid(output[coordinates_pb[0], coordinates_pb[1], 2])) * coord_scale,
                          bb_scale * self.anchor_box_ball[0] * m.exp(output[coordinates_pb[0], coordinates_pb[1], 3]),
                          bb_scale * self.anchor_box_ball[1] * m.exp(output[coordinates_pb[0], coordinates_pb[1], 4]))

        post1_detection = (sigmoid(output[coordinates_pp1[0], coordinates_pp1[1], 5]),
                           (coordinates_pp1[1] + sigmoid(output[coordinates_pp1[0], coordinates_pp1[1], 6])) * coord_scale,
                           (coordinates_pp1[0] + sigmoid(output[coordinates_pp1[0], coordinates_pp1[1], 7])) * coord_scale,
                           bb_scale * self.anchor_box_post[0] * m.exp(output[coordinates_pp1[0], coordinates_pp1[1], 8]),
                           bb_scale * self.anchor_box_post[1] * m.exp(output[coordinates_pp1[0], coordinates_pp1[1], 9]))

        post2_detection = (sigmoid(output[coordinates_pp2[0], coordinates_pp2[1], 5]),
                           (coordinates_pp2[1] + sigmoid(output[coordinates_pp2[0], coordinates_pp2[1], 6])) * coord_scale,
                           (coordinates_pp2[0] + sigmoid(output[coordinates_pp2[0], coordinates_pp2[1], 7])) * coord_scale,
                           bb_scale * self.anchor_box_post[0] * m.exp(output[coordinates_pp2[0], coordinates_pp2[1], 8]),
                           bb_scale * self.anchor_box_post[1] * m.exp(output[coordinates_pp2[0], coordinates_pp2[1], 9]))

        return ball_detection, post1_detection, post2_detection

    def get_coordinates_maximum(self, matrix):
        """
        Get the coordinates in a matrix which stores the biggest value.

        :param matrix: matrix to be analysed
        :type matrix: numpy matrix or ndarray
        :return i_max, j_max: the coordinates found
        :rtype: tuple of integers
        """
        maximum = 0
        i_max, j_max = -1, -1

        for i in range(np.shape(matrix)[0]):
            for j in range(np.shape(matrix)[1]):
                if (i_max, j_max) == (-1, -1):
                    maximum = matrix[i, j]
                    i_max, j_max = i, j
                elif matrix[i, j] > maximum:
                    maximum = matrix[i, j]
                    i_max, j_max = i, j

        return i_max, j_max

    def get_coordinates_second_maximum(self, matrix):
        """
        Get the coordinates in a matrix which stores the second biggest value.

        :param matrix: matrix to be analysed
        :type matrix: numpy matrix or ndarray
        :return i2_max, j2_max: the coordinates found
        :rtype: tuple of integers
        """
        i1_max, i2_max, j1_max, j2_max = -1, -1, -1, -1
        maximum_1, maximum_2 = 0, 0

        for i in range(np.shape(matrix)[0]):
            for j in range(np.shape(matrix)[1]):
                if (i1_max, j1_max) == (-1, -1):
                    maximum_1 = matrix[i, j]
                    i1_max, j1_max = i, j
                elif (i2_max, j2_max) == (-1, -1):
                    maximum_2 = matrix[i, j]
                    i2_max, j2_max = i, j
                elif matrix[i, j] > maximum_1:
                    maximum_2 = maximum_1
                    i2_max, j2_max = i1_max, j1_max
                    maximum_1 = matrix[i, j]
                    i1_max, j1_max = i, j
                elif matrix[i, j] > maximum_2:
                    maximum_2 = matrix[i, j]
                    i2_max, j2_max = i, j

        return i2_max, j2_max