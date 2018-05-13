def align(one_Line, costBook):
    Split_Line = one_Line.split(",")

    # Define an array with an extra row and col to represent a leading gap
    array = [[0] * (len(Split_Line[0]) + 1)
             for i in range(len(Split_Line[1]) + 1)]  # Zero fill array,

    xLine = Split_Line[1]
    yLine = Split_Line[0]
    for i in range(1, len(xLine) + 1):
        array[i][0] = array[i - 1][0] + int(costBook[xLine[i - 1] + '-'])
    for i in range(1, len(yLine) + 1):
        array[0][i] = array[0][i - 1] + int(costBook['-' + yLine[i - 1]])

    for i in range(1, len(xLine) + 1):
        for j in range(1, len(yLine) + 1):
            array[i][j] = min(array[i - 1][j] + diff(xLine[i - 1], '-', costBook),
                              array[i][j - 1] +
                              diff('-', yLine[j - 1], costBook),
                              array[i - 1][j - 1] + diff(xLine[i - 1], yLine[j - 1], costBook))
    stringBuilder(array, costBook, xLine, yLine)


def diff(x, y, cost):
    if x == y:
        return 0
    keyStr = x + y
    return int(costBook[keyStr])


def parseCost():
    fo = open("imp2cost.txt", "r+")
    data = fo.read().split()
    newData = []

    for i in range(len(data)):
        newData.append(data[i])  # get it by line

    for i in range(0, len(newData)):  # Split it by line seperated by commas
        newData[i] = newData[i].split(",")

    book = {}
    for i in range(1, len(newData[0])):
        for j in range(1, len(newData[i])):
            cur = newData[0][i] + newData[0][j]
            # Use letters at 0 to give dictionary key with val
            book[cur] = newData[i][j]
    return book


def stringBuilder(array, costBook, xLine, yLine):
    StringA, StringB = "", ""
    i, j = len(xLine), len(yLine)
    totalCost = array[i][j]

    while (i != 0 or j != 0):
        temp = array[i][j]
        if (array[i][j] == array[i][j - 1] + int(costBook['-' + yLine[j - 1]])):
            StringA += '-'
            StringB += yLine[j - 1]
            array[i][j] = 0
            j -= 1
        elif (array[i][j] == array[i - 1][j] + int(costBook[xLine[i - 1] + '-'])):
            StringA += xLine[i - 1]
            StringB += '-'
            array[i][j] = 0
            i -= 1
        elif (array[i][j] == array[i - 1][j - 1] + int(costBook[xLine[i - 1] + yLine[j - 1]])):
            StringA += xLine[i - 1]
            StringB += yLine[j - 1]
            array[i][j] = 0
            i -= 1
            j -= 1
    fo = open("imp2output.txt", "a+")
    fo.write(str(StringA[::-1]) + "," + str(StringB[::-1]) +
             ":" + str(totalCost))
    fo.write("\n")


if __name__ == "__main__":
    costBook = {}
    costBook = parseCost()
    fo = open("imp2input.txt", "r+")

    for i in fo:
        one_Line = i.split()[0]
        align(one_Line, costBook)
