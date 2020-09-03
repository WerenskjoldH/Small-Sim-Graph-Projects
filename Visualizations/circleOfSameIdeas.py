from p5 import *
import time

startTime = time.time()

numberOfCircles = 8
spaceOfCircle = 10
radiusCircles = 50
radiusAdditionaExpansion = 25
circles = []

totalTime = 0.0


def setup():
    size(numberOfCircles * (spaceOfCircle + radiusCircles),
         numberOfCircles * (spaceOfCircle + radiusCircles))
    title("p5 Circle of Same Ideas")

    for i in range(0, numberOfCircles):
        for j in range(0, numberOfCircles):
            circles.append((i*(spaceOfCircle+radiusCircles) + (spaceOfCircle+radiusCircles)/2,
                            j*(spaceOfCircle+radiusCircles) + (spaceOfCircle+radiusCircles)/2))

    stroke_weight(4)
    no_fill()


def draw():
    global totalTime

    background(Color(255, 255, 255))

    for i in range(0, numberOfCircles*numberOfCircles):
        curRadius = (radiusCircles+radiusAdditionaExpansion) * \
            cos(time.time() + circles[i][0])
        circle(circles[i], curRadius)


if __name__ == '__main__':
    run()
