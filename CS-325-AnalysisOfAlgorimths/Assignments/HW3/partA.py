from pulp import *
import matplotlib.pyplot as plt


def paperWork(x, b):
    plt.figure()
    xs = [1, 2, 3, 5, 7, 8, 10]
    ys = [3, 5, 7, 11, 14, 15, 19]
    points = [x * i + b for i in range(0, 15)]  # create straight line
    plt.plot(xs, ys, 'ro', label="points")
    plt.plot(points, label="Minimum max abs dev")
    plt.legend(loc="upper left")
    plt.title("Least Squares PartA")
    plt.savefig("partAResults.png")


def solveStuff():
    dataPoints = [[1, 3], [2, 5], [3, 7], [5, 11], [7, 14], [8, 15], [10, 19]]
    solver = LpProblem("Min max abs dev", LpMinimize)

    x, b, m = LpVariable("x"), LpVariable("b"), LpVariable("m", 0)
    solver += m

    for i in range(0, len(dataPoints)):
        # lower bound
        solver += m >= -(dataPoints[i][0] * x + b - dataPoints[i][1])
        # upper bound
        solver += m >= (x * dataPoints[i][0] + b - dataPoints[i][1])

    status = solver.solve()
    print (str(value(solver.objective)))
    print ("Val of x: " + str(value(x)))
    print ("Val of b: " + str(value(b)))
    print("SOLUTION: y = " + str(value(x)) + "x + " + str(value(b)))
    paperWork(float(value(x)), float(value(b)))


if __name__ == "__main__":
    solveStuff()
