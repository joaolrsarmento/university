import pygame
import math
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from pendulum import DampedPendulum
from utils import FRAME_TIME, WHITE, SCREEN_WIDTH, SCREEN_HEIGHT, PI, LINEAR_SPEED_CONSTANT, QUADRATIC_SPEED_CONSTANT, PENDULUM_LENGTH, PENDULUM_MASS

def main():
    # Simulating pendulum

    pygame.init()

    p1 = DampedPendulum(PENDULUM_LENGTH, PENDULUM_MASS, PI/3, LINEAR_SPEED_CONSTANT, QUADRATIC_SPEED_CONSTANT)

    w = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    w.fill(WHITE)
    view = True
    font = pygame.font.SysFont(None, 20)
    clock = pygame.time.Clock()

    while view:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                view = False

        save = p1.update()
        p1.draw()

        clock.tick(60)
        pygame.display.flip()
        w.fill(WHITE)

    df = pd.DataFrame()
    df['time'] = np.multiply(np.array(save[0]), 1 / 12)
    df['theta'] = save[1]
    df.to_excel('dados.xlsx')

    plt.plot(np.multiply(np.array(save[0]), 1 / 12), save[1])
    plt.show()

if __name__ == "__main__":
    main()
