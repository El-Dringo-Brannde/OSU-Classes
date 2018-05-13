from pulp import *
import math
import numpy as np
import matplotlib.pyplot as plt

# parses the Csv file into a list of lists


def parseData(fileName):
    fo = open(fileName, "r+")
    cleansedData, byLine = [], fo.read().split()
    for i in byLine:
        cleansedData.append(i.split(";"))
    return cleansedData


'''
------------------------ Returns a list of lists in the fashion of ------------------------------
['STATION', 'DATE', 'TMAX', 'TMIN', 'year', 'month', 'day', 'average', 'day']
['GHCND:USC00351862', '19520501', '144', '44', '1952', '5', '1', '9.4', '0']
['GHCND:USC00351862', '19520502', '172', '0', '1952', '5', '2', '8.6', '1']
                                ....
'''


def solve(dataArray):
    dataPoints = []
    for i in range(1, len(dataArray)):
        point = [float(dataArray[i][-1]), float(dataArray[i][-2])]
        dataPoints.append(point)
    solver = LpProblem("Temperature Min Max", LpMinimize)

    x, x1, x2, x3, x4, x5, m = LpVariable("x"), LpVariable("x1"), LpVariable(
        "x2"), LpVariable("x3"), LpVariable("x4"), LpVariable("x5"), LpVariable("m", 0)
    solver += m

    for j in range(0, len(dataPoints)):
        solver += m >= -(x + (x1 * dataPoints[j][0]) + (x2 * math.cos((2.0 * math.pi * dataPoints[j][0]) / 365.25)) + (x3 * math.sin((2.0 * math.pi * dataPoints[j][0]) / 365.25)) + (
            x4 * math.cos((2.0 * math.pi * dataPoints[j][0]) / (365.25 * 10.7))) + (x5 * math.sin((2.0 * math.pi * dataPoints[j][0]) / (365.25 * 10.7))) - dataPoints[j][1])
        solver += m >= (x + (x1 * dataPoints[j][0]) + (x2 * math.cos((2.0 * math.pi * dataPoints[j][0]) / 365.25)) + (x3 * math.sin((2.0 * math.pi * dataPoints[j][0]) / 365.25)) + (
            x4 * math.cos((2.0 * math.pi * dataPoints[j][0]) / (365.25 * 10.7))) + (x5 * math.sin((2.0 * math.pi * dataPoints[j][0]) / (365.25 * 10.7))) - dataPoints[j][1])

    status = solver.solve()
    print (str(value(solver.objective)))
    print ("Val of x/slope: " + str(value(x)))
    print ("Val of x1: " + str(value(x1)))
    print ("Val of x2: " + str(value(x2)))
    print ("Val of x3: " + str(value(x3)))
    print ("Val of x4: " + str(value(x4)))
    print ("Val of x5: " + str(value(x5)))


if __name__ == "__main__":
    assert(len(sys.argv) > 1), "Need to specify a file my friend!"
    cleanData = parseData(sys.argv[1])
    # print(cleanData) #Print if you want to blow up your screen
    solve(cleanData)
