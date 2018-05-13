import matplotlib.pyplot as plt
import sys
import numpy as np

plt.figure()
ax = plt.gca()
timeFile = open("AvgTimes.txt", "r+")
data = timeFile.read().split()
for i in range(0, len(data)):
    data[i] = float(data[i])


inputSize = [500, 1000, 2000, 3000, 4000, 5000]
plt.plot(inputSize, data, marker="o", label="SequenceAlignmentLOG")
ax.set_yscale('log')
ax.set_xscale('log')
plt.legend(loc="upper left")


plt.ylabel('Time (Seconds)')
plt.xlabel('Input size')
PDF_File = "EqualLengthAlignmentLOG.png"
plt.savefig(PDF_File)
