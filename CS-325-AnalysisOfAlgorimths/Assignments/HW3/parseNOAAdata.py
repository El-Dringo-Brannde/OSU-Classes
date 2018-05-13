import csv


def paperWork(cleanData, year, day, month, Avg, Max, Min, ID):
    fo = open("./SF.csv", "a+")
    fo.write(str(cleanData[0]) + ";" + str(cleanData[1]) + ";" + str(Max) + ";" + str(Min)
             + ";" + str(year) + ";" + str(month) + ";" + str(day) +
             ";" + str(Avg) + ";" + str(ID) + "\n")


def toFarenheit(data):
    return str((data - 32) * 0.555555556)


def parseData():
    temp = []
    cleanData = []
    with open('./916041.csv') as csvFile:
        reader = csv.reader(csvFile, delimiter=',', quotechar='|')
        for row in reader:
            temp.append(row)
    for i in range(1, len(temp)):
        longTime = temp[i][1]
        year = longTime[:4]
        month = longTime[4:6]
        day = longTime[6:8]
        cleanAvg = toFarenheit(int(temp[i][2]))[:5]
        cleanMax = toFarenheit(int(temp[i][3]))[:5]
        cleanMin = toFarenheit(int(temp[i][4]))[:5]
        print(cleanAvg, cleanMax, cleanMin)
        if (float(cleanAvg) > -10 and float(cleanAvg) < 40):
            print(year, month, day, cleanAvg, cleanMax, cleanMin)
            paperWork(temp[i], year, day, month,
                      cleanAvg, cleanMax, cleanMin, i)


if __name__ == "__main__":
    parseData()
