from copy import *

def kwic(doc, periodsToBreaks, ignorewords, listpair):
	if doc:
		if "\n" in doc: #checks to see if there is a line break to iterate through
						# both mini arrays
			Comp_line = doc.splitlines() #splits the two strings by the \n character
			finalarr = test(Comp_line)


		else: #If there are no line splits go here
			Parsed_line = []
			Parsed_line.append(doc.split())
			longarr = []
			finalarr = []
			dumb = [0]
			for i in (range(len(Parsed_line[0]))):
				front = Parsed_line[0].pop(0)
				Parsed_line[0].append(front)
				b = deepcopy(Parsed_line)	#prevents from writing over while loop iterates
				longarr.append([b[0]])	#puts rotated string on longarr
				longarr.append(dumb)	#includes line index
		
			size = int(len(longarr))
			i = 0
			while (i != size):
				finalarr.append(tuple(longarr[i]+longarr[i+1]))	#goes through and adds string
																	#and index
				i += 2
			finalarr.sort()
			for i in range(len(finalarr)):
				print (finalarr[i])
		print (finalarr)
		return finalarr

	list = []
	return list

def test(Comp_line):
	Parsed_line = []
	index = []
	for i in (range(len(Comp_line))): #runs the length of the lines given
		Parsed_line.append(Comp_line[i].split())	#break the words of each line into own array piece
		index.append(i)	#keeps line index for each string 
		d = deepcopy(index)
		if d[i] != 0:
			d.pop(0)
		Parsed_line.append(d)

	print (Parsed_line)
	longarr = []	#Creates the ending array to hold the tuples
	for i in (range(len(Parsed_line) - 1)):
		size = len(Parsed_line[i])
		if (Parsed_line[i] != [0]):
			for j in range(size):
				front = Parsed_line[i].pop(0)
				arrsize = len(Parsed_line[i])
				Parsed_line[i].insert(arrsize, front)
				c = deepcopy(Parsed_line)
				longarr.append(c[i])
				longarr.append(c[i+1])
	finalarr = []

	size = int(len(longarr))
	i = 0
	while (i != size):
		finalarr.append(tuple([longarr[i]] + longarr[i+1]))
		i+=2
	finalarr.sort()
	for i in range(len(finalarr)):
		print(finalarr[i])
	print ("\n")
	print (finalarr)
	return finalarr
