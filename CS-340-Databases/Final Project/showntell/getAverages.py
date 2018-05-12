
def getAverages(clean):
    for i in range(0, len(clean)):
        curAdd = clean[i][0]
        curStreet = clean[i][1]
        curApt = clean[i][2]
        for j in range(0, len(clean[i])):
            if (clean[i][j] ==)
            print(clean[i][j])


if __name__ == "__main__":
    f = open("Delivery.csv", "r")
    data = f.read().split("\n")
    clean = []
    for i in data:
        clean.append(i.split(","))
    print (clean)
    getAverages(clean)
