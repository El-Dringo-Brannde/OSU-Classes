import random
import sys


output_Holder = []
for i in range(int(sys.argv[1])):  # run until CLI arg
    x_Value = random.randrange(0, 10000)  # Generate 0-10000
    y_Value = random.randrange(0, 10000)
    output_Holder.append([x_Value, y_Value])

x = 0
# Prune out any doubles that might have occured in the generation
for i in output_Holder:
    j = x + 1
    while (j + 1 <= len(output_Holder)):
        nextVal = output_Holder[j]
        if (nextVal == i):  # If the next value is the same as current
            del [output_Holder[j]]  # delete any double that might appear
        j += 1
    x += 1

fout = open(sys.argv[2], "w+")
for i in output_Holder:
    fout.write(str(i[0]))
    fout.write(" ")
    fout.write(str(i[1]))
    fout.write("\n")

fout.close()
