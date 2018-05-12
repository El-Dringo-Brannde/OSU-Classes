from copy import *
from string import *
def kwic(doc, periodsToBreaks, ignorewords, listpair):
	if doc:
		if periodsToBreaks == True:
			line_by_period = []
			astring = ""
			stringlen = len(doc)
			for i in range(stringlen):
				astring+=doc[i]
				if ((doc[i-1] >= chr(97) and doc[i-1] <= chr(122)) #test between lowercase characters
				and doc[i] == '.' and doc[i+1] == ' '):	#test for '.' and ' ' after period
					line_by_period.append(astring)
					astring = ""

			line_by_period.append(astring)
			longarr = Parse_document(line_by_period, ignorewords)

		elif "\n" in doc: #checks to see if there is a line break to iterate through
			Comp_line = doc.splitlines() #splits the two strings by the \n character
			longarr = Parse_document(Comp_line,ignorewords)

		else: #If there are no line splits go here
			Parsed_line = []
			Parsed_line.append(doc.split())
			longarr = proc_no_breaks(Parsed_line, ignorewords)

	list = []
	return list

def proc_no_breaks(Comp_line,ignorewords):
	finalarr = []
	Parsed_line = Comp_line
	dumb=[0]
	temparr = []
	for i in (range(len(Parsed_line[0]))):
		front = Parsed_line[0].pop(0)
		Parsed_line[0].append(front)
		b = deepcopy(Parsed_line)
		if len(ignorewords) != 0:
			for q in range(len(ignorewords)):
				if b[0] != ignorewords[q]:
					temparr.append(b)
					temparr.append(dumb)
		else:
			temparr.append(b)
			temparr.append(dumb)
	size = int(len(longarr))
	i = 0
	while (i != size):
		finalarr.append(tuple(temparr[i]+temparr[i+1]))
		i += 2
	finalarr.sort()
	print (finalarr)
	return finalarr


def Parse_document(Comp_line,ignorewords):
	Parsed_line = []
	index = []
	for i in (range(len(Comp_line))): #runs the length of the lines given
		Parsed_line.append(Comp_line[i].split())	#break the words of each line into own array piece
		index.append(i)
		d = deepcopy(index)
		while (len(d) != 1):
			d.pop(0)
		Parsed_line.append(d)
	longarr = []	#Creates the ending array to hold the tuples
	i = 0
	finalarr = []
	while i != int(len(Parsed_line)):
		size = len(Parsed_line[i])
		for j in range(size):
				front = Parsed_line[i].pop(0)
				arrsize = len(Parsed_line[i])
				Parsed_line[i].insert(arrsize, front)
				c = deepcopy(Parsed_line)
				if len(ignorewords) != 0:
					redflag = 0
					for q in range(len(ignorewords)):
						if c[0][0] == ignorewords[q]:
							redflag = 1
					if redflag != 0:
						pass
					else:
						longarr.append(c[i])
						longarr.append(c[i+1])
				else:
					longarr.append(c[i])
					longarr.append(c[i+1])
		i += 2
	size = int(len(longarr))
	i = 0
	while (i != size):
		finalarr.append(tuple([longarr[i]] + longarr[i+1]))
		i+=2
	finalarr.sort()
	#for i in range(len(finalarr)):
	#	print(finalarr[i])
	print(finalarr)
	return finalarr
