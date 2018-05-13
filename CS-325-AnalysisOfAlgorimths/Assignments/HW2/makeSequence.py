import random
import sys


def buildSequence():
    fo = open("input" + sys.argv[1] + ".txt", "a+")
    string1, string2 = [], []
    halfsies = int(sys.argv[1]) / 2
    book = {0: 'A', 1: 'C', 2: 'G', 3: 'T'}
    for i in range(0, int(halfsies)):
        stringA = random.randrange(0, 4)
        stringB = random.randrange(0, 4)
        if stringA == 0:  # "A" case
            string1.append(book[stringA])
            string2.append(book[stringB])
        elif stringA == 1:  # "C" case
            string1.append(book[stringA])
            string2.append(book[stringB])
        elif stringA == 2:  # "G" case
            string1.append(book[stringA])
            string2.append(book[stringB])
        elif stringA == 3:  # "T" case
            string1.append(book[stringA])
            string2.append(book[stringB])

    for i in range(0, int(halfsies)):
        fo.write(string1[i])
    fo.write(",")
    for i in range(0, int(halfsies)):
        fo.write(string2[i])
    fo.write("\n")
    fo.close()


if __name__ == "__main__":
    buildSequence()
