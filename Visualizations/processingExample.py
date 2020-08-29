from p5 import *


def setup():
    size(640, 360)
    # no_stroke()
    background(204)


def draw():
    fill(0, 255, 0)

    line((320, 180), (mouse_x, mouse_y))


def key_pressed(event):
    background(204)


run()
