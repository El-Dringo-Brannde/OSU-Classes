from copy import *

def kwic(doc, periodsToBreaks, ignorewords, listpair):
	if doc:
		if periodsToBreaks == True:
			preperiod = []
			astring = ""
			stringlen = len(doc)
			for i in range(stringlen):
				astring+=doc[i]
				if ((doc[i-1] >= chr(97) and doc[i-1] <= chr(122)) #test between lowercase characters
				and doc[i] == '.' and doc[i+1] == ' '): #test for '.' and ' ' after period
					preperiod.append(astring)
					astring = ""

<<<<<<< Updated upstream
			preperiod.append(astring)
			finalarr = Parse_document(preperiod)


=======
			line_by_period.append(astring.lower())
			longarr = Parse_document(line_by_period)
        elif ignorewords == True:
            print ("Fart")
>>>>>>> Stashed changes
		elif "\n" in doc: #checks to see if there is a line break to iterate through
						# both mini arrays
			Comp_line = doc.splitlines() #splits the two strings by the \n character
			finalarr = Parse_document(Comp_line)

		else: #If there are no line splits go here
			Parsed_line = []
			Parsed_line.append(doc.split())
			longarr = []
			finalarray = []
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
				finalarray.append(tuple(longarr[i]+longarr[i+1]))	#goes through and adds string
																	#and index
				i += 2
			finalarray.sort()
			for i in range(len(finalarray)):
				print (finalarray[i])
			print (finalarray)
		return finalarr

	list = []
	return list



def Parse_document(Comp_line):
	Parsed_line = []
	index = []
	for i in (range(len(Comp_line))): #runs the length of the lines given
		Parsed_line.append(Comp_line[i].split())	#break the words of each line into own array piece
		index.append(i)	#keeps line index for each string 
		d = deepcopy(index)
		while (len(d) != 1):
			d.pop(0)
		Parsed_line.append(d)

	longarr = []	#Creates the ending array to hold the tuples
	i = 0 
	while i != int(len(Parsed_line)):
		size = len(Parsed_line[i])
		for j in range(size):
			front = Parsed_line[i].pop(0)
			arrsize = len(Parsed_line[i])
			Parsed_line[i].insert(arrsize, front)
			c = deepcopy(Parsed_line)
			longarr.append(c[i])
			longarr.append(c[i+1])
		i += 2
	finalarray = []
	size = int(len(longarr))
	i = 0
	while (i != size):
		finalarray.append(tuple([longarr[i]] + longarr[i+1]))
		i+=2
	finalarray.sort()
	for i in range(len(finalarray)):
		print(finalarray[i])
	print(finalarray)
	return finalarray
