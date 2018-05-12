from copy import *

def kwic(doc,periodsToBreaks, ignoreWords, listPairs):
	if doc:
		finalarray = []
		temparr = []
		real = []
		if listPairs == True and periodsToBreaks == True:
			temparr = proc_periods(doc)
			line_by_period = []
			for i in range(len(temparr)):
				real.append(temparr[i])
				fart = real[i].split()
				line_by_period.append(real[i].split())
			real = line_by_period
			proced_pairs = proc_linepairs(real,finalarray,periodsToBreaks)
			finalarray = Parse_document(temparr,ignoreWords)
			finalarray.append(proced_pairs)

			return finalarray
		elif listPairs == True and periodsToBreaks == False:
			real = doc.splitlines()
			unspitlines = deepcopy(real)
			for i in range(len(real)):
				real[i] = real[i].split()
			proced_pairs = proc_linepairs(real,finalarray,periodsToBreaks)
			finalarray = Parse_document(unspitlines,ignoreWords)
			finalarray.append(proced_pairs)
			print(finalarray)

		elif listPairs == True:
			proced_pairs = proc_linepairs(real,finalarray,periodsToBreaks)
			return proced_pairs
		elif periodsToBreaks == True:
			line_by_period = proc_periods(doc)
			finalarray = Parse_document(line_by_period, ignoreWords)

		elif "\n" in doc: #checks to see if there is a line break to iterate through
			Comp_line = doc.splitlines() #splits the two strings by the \n character
			finalarray = Parse_document(Comp_line,ignoreWords)

		else: #If there are no line splits go here
			Parsed_line = []
			Parsed_line.append(doc.split())
			finalarray = proc_no_breaks(Parsed_line, ignoreWords)

		print("\n")
		for i in range(len(finalarray)):
			print(finalarray[i])
		print(finalarray)
		return finalarray

	list = []
	return list



def proc_periods(doc):
	line_by_period = []
	astring = ""
	stringlen = len(doc)
	for i in range(stringlen):
		astring+=doc[i]
		if ((doc[i-1] >= chr(97) and doc[i-1] <= chr(122)) #test between lowercase characters
		and doc[i] == '.' and doc[i+1] == ' '):	#test for '.' and ' ' after period
			if astring[0] == " ":
				astring[0:]
			line_by_period.append(astring)
			astring = ""
	line_by_period.append(astring)
	return line_by_period



def proc_linepairs(real,finalarray,periodsToBreaks):
	for i in range(len(real)):
		for j in range(len(real[i])):
			real[i][j] = real[i][j].lower()
	for b in (range(len(real))):
		for c in (range(len(real[b]))):
			wordsize = len(real[b][c])
			d= 0
			while d != wordsize:
				letter = real[b][c][d]
				if (letter == chr(33)):
					removed = real[b][c][d].replace("!","")
					cleanword = real[b][c][:d] + removed +real[b][c][d+1:]
					real[b][c] = cleanword
					wordsize -= 1
				elif letter == chr(46):
					removed = real[b][c][d].replace(".","")
					cleanword = real[b][c][:d] + removed +real[b][c][d+1:]
					real[b][c] = cleanword
					wordsize -= 1
				elif letter == chr(63):
					removed = real[b][c][d].replace("?","")
					cleanword = real[b][c][:d] + removed +real[b][c][d+1:]
					real[b][c] = cleanword
					wordsize -= 1
				elif letter == chr(44):
					removed = real[b][c][d].replace(",","")
					cleanword = real[b][c][:d] + removed +real[b][c][d+1:]
					real[b][c] = cleanword
					wordsize -= 1
				elif letter == chr(58):
					removed = real[b][c][d].replace(":","")
					cleanword = real[b][c][:d] + removed +real[b][c][d+1:]
					real[b][c] = cleanword
					wordsize -= 1
				else:
					d +=1


	wordpairs = []
	t = 0
	greenflag = 1
	for i in range(len(real)-1): #goes the number of lines
		for f in range(len(real[i]) -1):#goes the number of words in line
			spot1 = real[i][f]
			t = f+1	#prevents from checking before spot1
			while t != int(len(real[i])):#goes to length of line
				spot2 = real[i][t]	#grabs the second word
				q = i+1		#prevents going back before the current string iteration
				while q != len(real): #goes length from where next line is to end
					for x in range(len(real[q])): #goes the number of words in next line
						check1 = real[q][x]
						if (spot1 == check1 or spot2 == check1):
							w = x +1 #prevents check2 from starting back over in string
							while w != len(real[q]):
								check2 = real[q][w]
								if (spot1 == check1 or spot1 == check2) and (spot2 == check2 or spot2 == check1) and (spot1 != spot2):
									wordpairs.append(spot1 + " " +spot2)
								w +=1
					q += 1
				t += 1
	finpairs = []
	holder = []
	for v in range(len(wordpairs)):
		wordcount = wordpairs.count(wordpairs[v])
		if holder.count(wordpairs[v]) == 0:
				greenflag = 1
		if greenflag == 1:
			if wordcount == 1:
				wordcount += 1
	#		wordpairs[v] = wordpairs[v].split()
			holder.append(wordpairs[v])
			holder.append(wordcount)
			greenflag = 0

	i = 0
	while i != len(holder):
		holder[i] = holder[i].split()
		finpairs.append(tuple([tuple(holder[i])]) + tuple([holder[i+1]]))
		i +=  2
	finpairs.sort()
	return finpairs



def proc_no_breaks(Comp_line,ignoreWords):
	finalarr = []
	Parsed_line = Comp_line
	dumb=[0]
	temparr = []
	for i in (range(len(Parsed_line[0]))):
		front = Parsed_line[0].pop(0)
		Parsed_line[0].append(front)
		b = deepcopy(Parsed_line)
		if len(ignoreWords) != 0:
			for q in range(len(ignoreWords)):
				if b[0] != ignoreWords[q]:
					temparr.append(b)
					temparr.append(dumb)
		else:
			temparr.append(b)
			temparr.append(dumb)
	size = int(len(temparr))
	i = 0
	while (i != size):
		finalarr.append(tuple(temparr[i]+temparr[i+1]))
		i += 2
	finalarr.sort(key=lambda el: el[0][0].lower())
	i = 0
	for i in range(len(finalarr)):
		print(finalarr[i])
	print("\n")
	return finalarr




def Parse_document(Comp_line,ignoreWords):
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
				if len(ignoreWords) != 0:
					redflag = 0
					for q in range(len(ignoreWords)):
						if c[0][0] == ignoreWords[q]:
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
	finalarr.sort(key=lambda el:el[0][0].lower())
	for i in range(len(finalarr)):
		print(finalarr[i])
	print("\n")
	return finalarr
