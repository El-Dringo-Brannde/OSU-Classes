import numpy as np
import matplotlib.pyplot as plt
import sys


def doWork(file):
    fo = open(file, "r+")
    data = fo.read().split("\n")
    points = []
    plt.figure()
    print(data)


if __name__ == "__main__":
    assert(len(sys.argv) > 1), "Give me a file to read!"  # require a file
    doWork(sys.argv[1])
