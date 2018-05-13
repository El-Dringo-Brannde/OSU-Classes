def normalizeData():
    fo = open("timeLog.txt", "r+")
    data = fo.read().split()
    collector = 0
    for i in data:
        collector += float(i)

    avgTime = collector / len(data)
    end = open("AvgTimes.txt", "a+")
    end.write(str(avgTime) + "\n")
    print(avgTime)


if __name__ == "__main__":
    normalizeData()
