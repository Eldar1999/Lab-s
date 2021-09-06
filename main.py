import numpy
from scipy import stats
import matplotlib.pyplot as plt


def normal_dist(x, mean, sd):
    prob_density = (numpy.pi * sd) * numpy.exp(-0.5 * ((x - mean) / sd) ** 2)
    return prob_density


X = numpy.array([69, 74, 68, 70, 72, 67, 66, 70, 76, 68, 72, 79, 74, 67, 66, 71, 74, 75, 75, 76], numpy.float64)
Y = numpy.array([153, 175, 155, 135, 172, 150, 115, 137, 200, 130, 140, 265, 185, 112, 140, 150, 165, 185, 210, 220],
                numpy.float64)
X.sort()
print(X)
print("Mean ", end="")
print(numpy.mean(X))
print("Med ", end="")
print(numpy.median(X))
print("Mode ", end="")
print(stats.mode(X))
print("Disp ", end="")
print(stats.variation(Y))
print("Norm")
plt.plot(X, normal_dist(X, numpy.mean(X), numpy.std(X)))
plt.xlim(60, 82)
plt.savefig("test.png")
print(normal_dist(X, numpy.mean(X), numpy.std(X)))
print(0)
print("Corr X Y", end="")

print(numpy.correlate(X, Y))
