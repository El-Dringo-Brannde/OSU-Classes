from copy import *

def kwic(doc,periodsToBreaks, ignorewords, listpair):
	if doc:
		split = []
		split.append(doc.split())
		longarr = []
		finalarray = []
		dumb = [0]
		for i in (range(len(split[0]))):
			front = split[0].pop(0)
			split[0].append(front)
			b = deepcopy(split)
			longarr.append([b[0]])
			longarr.append(dumb)
			
		size = int(len(longarr))
		i = 0
		while (i != size):
			finalarray.append(tuple(longarr[i]+longarr[i+1]))
			i += 2
		for i in range(len(finalarray)):
			print (finalarray[i])
			
		return finalarray

	list = []
	return list

