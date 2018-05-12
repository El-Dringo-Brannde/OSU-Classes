from copy import *

def kwic(doc, periodsToBreaks, ignorewords, listpair):
	if doc:
		Parsed_line = []
		Parsed_line.append(doc.split())
		longarr = []
		finalarray = []
		dumb = [0]
		for i in (range(len(Parsed_line[0]))):
			front = Parsed_line[0].pop(0)
			Parsed_line[0].append(front)
			b = deepcopy(Parsed_line)
			longarr.append([b[0]])
			longarr.append(dumb)
			
		size = int(len(longarr))
		i = 0
		while (i != size):
			finalarray.append(tuple(longarr[i]+longarr[i+1]))
			i += 2
		finalarray.sort()
		for i in range(len(finalarray)):
			print (finalarray[i])
		print (finalarray)
		return finalarray

	list = []
	return list
