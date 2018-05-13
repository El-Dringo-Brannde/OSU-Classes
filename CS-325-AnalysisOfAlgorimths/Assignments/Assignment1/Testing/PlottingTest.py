import matplotlib.pyplot as plt
import sys
import numpy as np

plt.figure()

PointArray = []
BruteForceFile = open(sys.argv[1], "r+")
Brutevalue = BruteForceFile.read()
BruteForce_time_Values = Brutevalue.split()
BruteForceFile.close()

NaiveFile = open(sys.argv[2], "r+")
Naivevalue = NaiveFile.read()
NaiveTimeValues = Naivevalue.split()
NaiveFile.close()

EnhancedFile = open(sys.argv[3], "r+")
EnhancedValue = EnhancedFile.read()
EnhancedTime = EnhancedValue.split()
EnhancedFile.close()


i = 0

for i in range(len(BruteForce_time_Values)):
    BruteForce_time_Values[i] = float(BruteForce_time_Values[i])
i = 0
for i in range(len(NaiveTimeValues)):
    NaiveTimeValues[i] = float(NaiveTimeValues[i])
i = 0

for i in range(len(EnhancedTime)):
    EnhancedTime[i] = float(EnhancedTime[i])


# create some data
inputSize = [100, 1000, 2000, 3000, 4000, 5000,
             6000, 7000, 8000, 9000, 10000]
# plot the two lines
plt.axis([10, 10000, 0, 100])
plt.plot(inputSize, BruteForce_time_Values, label="BruteForce")
plt.plot(inputSize, NaiveTimeValues, label="NaiveDnC")
plt.plot(inputSize, EnhancedTime, label="EnhancedDnC")
plt.legend(loc="upper left")


plt.ylabel('Time (Seconds)')
plt.xlabel('Input size')
plt.title("Find closest pair of points")
PDF_File = "AllAlgorithms.png"
plt.savefig(PDF_File)
