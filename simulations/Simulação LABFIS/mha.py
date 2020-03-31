from vpython import *


def getYPosition(A, m, k, b, t):
    if t < 0:
        return 0
    return A*exp((-1)*b*t/(2*m))*cos(sqrt(k/m - b**2/(4*(m**2)))*t)


def start(amplitude, mass_object, mass_spring, k_constant, b_constant, ref_file):

    # ref_file.write('Tempo Posição\n')
    pivot = vector(0, 20, 0)
    equil = vector(0, -10, 0)
    roof = box(pos=pivot, size=vector(10, 1, 10), color=color.green)

    length = 4
    height = 4
    width = 4

    object = box(pos=pivot + equil, size=vector(length, height, width))
    # velocity = arrow(pos=object.pos + vector(-6, 0, 0), axis=vector(0, 0, 0))
    spring = helix(pos=pivot, axis=object.pos - pivot, radius=2)
    previous_variation = vector(0, 0, 0)

    for t in range(0, 10000, 1):
        # ref_file.write(str(t/100) +' '+str(getYPosition(amplitude, mass_object + mass_spring/3, k_constant, b_constant, t/100)) + '\n')
        rate(100)
        vector_variation = vector(0, getYPosition(
            amplitude, mass_object + mass_spring/3, k_constant, b_constant, t/100), 0)
        object.pos = equil + vector_variation
        # velocity.axis = 1.0*(vector_variation - previous_variation)/(0.01)
        # velocity.pos = object.pos + vector(-6, 0, 0)
        # velocity_text = text(text = str(velocity.axis.mag) + " m/s", pos = roof.pos + vector(-1,3,0), color = color.white)
        spring.axis = object.pos - spring.pos
        previous_variation = vector_variation


amplitude = 5
mass_object = 0.126 + 0.0218
mass_spring = 0.0502
k_constant = 36
b_constant = 0.03

ref_file = open('ans.txt', 'w')

start(amplitude, mass_object, mass_spring, k_constant, b_constant, ref_file)
