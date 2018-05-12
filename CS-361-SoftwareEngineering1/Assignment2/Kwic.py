from copy import *

def kwic(doc,periodsToBreaks = False, ignoreWords = [], listPairs =  False ):
	if doc:
		Final_Array = []
		Unsplit_lines = []
		Parsed_Array = []
		if listPairs == True and periodsToBreaks == True:
			Unsplit_lines = Proccess_Periods(doc)
			line_by_period = []
			for i in range(len(Unsplit_lines)):
				Parsed_Array.append(Unsplit_lines[i])
				holder = Parsed_Array[i].split()
				line_by_period.append(Parsed_Array[i].split())
			Parsed_Array = line_by_period
			Processed_pairs = proc_linepairs(Parsed_Array,Final_Array,periodsToBreaks)
			Final_Array = Parse_document(Unsplit_lines,ignoreWords)
			Final_Array.append(Processed_pairs)

		elif listPairs == True and periodsToBreaks == False:
			Parsed_Array = doc.splitlines()
			unspitlines = deepcopy(Parsed_Array)
			for i in range(len(Parsed_Array)):
				Parsed_Array[i] = Parsed_Array[i].split()
			Processed_pairs = proc_linepairs(Parsed_Array,Final_Array,periodsToBreaks)
			Final_Array = Parse_document(unspitlines,ignoreWords)
			Final_Array.append(Processed_pairs)

		elif listPairs == True: #Probably won't be ran
			Processed_pairs = proc_linepairs(Parsed_Array,Final_Array,periodsToBreaks)
			return Processed_pairs
		elif periodsToBreaks == True: #If there are periods to breaks w/o listpairs
			line_by_period = Proccess_Periods(doc)
			Final_Array = Parse_document(line_by_period, ignoreWords)

		elif "\n" in doc: #checks to see if there is a line break to iterate through
			Comp_line = doc.splitlines() #splits the two strings by the \n character
			Final_Array = Parse_document(Comp_line,ignoreWords)

		else: #If there are no line splits go here
			Parsed_line = []
			Parsed_line.append(doc.split())
			Final_Array = Proccess_No_Breaks(Parsed_line, ignoreWords)
			
		return Final_Array
	list = []
	return list


#Requires format of ['This is a sentence','...']
def Proccess_Periods(doc):
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
	return line_by_period


# Requires format of [['this', 'a','sentence'], '...']
def proc_linepairs(Parsed_Array,Final_Array,periodsToBreaks):
	for i in range(len(Parsed_Array)):
		for j in range(len(Parsed_Array[i])):
			Parsed_Array[i][j] = Parsed_Array[i][j].lower()
	for b in (range(len(Parsed_Array))):
		for c in (range(len(Parsed_Array[b]))):
			wordsize = len(Parsed_Array[b][c])
			d = 0
			while d != wordsize: #Removes any puncuation in the strings
				letter = Parsed_Array[b][c][d]
				if (letter == chr(33)):
					removed = Parsed_Array[b][c][d].replace("!","")
					cleanword = Parsed_Array[b][c][:d] + removed +Parsed_Array[b][c][d+1:]
					Parsed_Array[b][c] = cleanword
					wordsize -= 1
				elif letter == chr(46):
					removed = Parsed_Array[b][c][d].replace(".","")
					cleanword = Parsed_Array[b][c][:d] + removed +Parsed_Array[b][c][d+1:]
					Parsed_Array[b][c] = cleanword
					wordsize -= 1
				elif letter == chr(63):
					removed = Parsed_Array[b][c][d].replace("?","")
					cleanword = Parsed_Array[b][c][:d] + removed +Parsed_Array[b][c][d+1:]
					Parsed_Array[b][c] = cleanword
					wordsize -= 1
				elif letter == chr(44):
					removed = Parsed_Array[b][c][d].replace(",","")
					cleanword = Parsed_Array[b][c][:d] + removed +Parsed_Array[b][c][d+1:]
					Parsed_Array[b][c] = cleanword
					wordsize -= 1
				elif letter == chr(58):
					removed = Parsed_Array[b][c][d].replace(":","")
					cleanword = Parsed_Array[b][c][:d] + removed +Parsed_Array[b][c][d+1:]
					Parsed_Array[b][c] = cleanword
					wordsize -= 1
				else:
					d +=1

	wordpairs = []
	t = 0
	greenflag = 1
	for i in range(len(Parsed_Array)-1): #goes the number of lines
		for f in range(len(Parsed_Array[i]) -1):#goes the number of words in line
			spot1 = Parsed_Array[i][f]
			t = f+1	#prevents from checking before spot1
			while t != int(len(Parsed_Array[i])):#goes to length of line
				spot2 = Parsed_Array[i][t]	#grabs the second word
				q = i+1		#prevents going back before the current string iteration
				while q != len(Parsed_Array): #goes length from where next line is to end
					for x in range(len(Parsed_Array[q])): #goes the number of words in next line
						check1 = Parsed_Array[q][x]
						if (spot1 == check1 or spot2 == check1):
							w = x +1 #prevents check2 from starting back over in string
							while w != len(Parsed_Array[q]): #repeats while the end of the line hasn't been hit
								check2 = Parsed_Array[q][w]
								if (spot1 == check1 or spot1 == check2) and (spot2 == check2 or spot2 == check1) and (spot1 != spot2):
									wordpairs.append(spot1 + " " +spot2)
								w +=1
					q += 1
				t += 1

	Final_Word_Pairs = []
	holder = []
	for v in range(len(wordpairs)):
		wordcount = wordpairs.count(wordpairs[v])
		if holder.count(wordpairs[v]) == 0:
				greenflag = 1   #If the word pair hasn't been found already found
		if greenflag == 1:
			if wordcount == 1:
				wordcount += 1
			holder.append(wordpairs[v])
			holder.append(wordcount)
			greenflag = 0

	i = 0
	while i != len(holder):
		holder[i] = holder[i].split()
		holder[i].sort()
		if len(holder[i]) == 2:
			Final_Word_Pairs.append(tuple([tuple(holder[i])]) + tuple([holder[i+1]])) #Formatting
		i +=  2
		Final_Word_Pairs.sort()
	return Final_Word_Pairs



def Proccess_No_Breaks(Comp_line,ignoreWords):
	Final_Array = []
	Parsed_line = Comp_line
	Zero_Line_Index=[0]
	temparr = []
	for i in (range(len(Parsed_line[0]))):
		front = Parsed_line[0].pop(0)
		Parsed_line[0].append(front)
		b = deepcopy(Parsed_line) #Makes a deepcopy to prevent rewriting
		if len(ignoreWords) != 0:
			for q in range(len(ignoreWords)):
				if b[0] != ignoreWords[q]:
					temparr.append(b)
					temparr.append(Zero_Line_Index)
		else:
			temparr.append(b)
			temparr.append(Zero_Line_Index)
	size = int(len(temparr))
	i = 0
	while (i != size):
		Final_Array.append(tuple(temparr[i]+temparr[i+1]))
		i += 2
		Final_Array.sort(key=lambda el: el[0][0].lower()) #Sorts case insensitive
	i = 0
	return Final_Array




def Parse_document(Comp_line,ignoreWords):
	Parsed_line = []
	Index_Tracker = []
	for i in (range(len(Comp_line))): #runs the length of the lines given
		Parsed_line.append(Comp_line[i].split())	#break the words of each line into own array piece
		Index_Tracker.append(i)
		d = deepcopy(Index_Tracker)
		while (len(d) != 1):
			d.pop(0)
		Parsed_line.append(d)
	longarr = []	#Creates the ending array to hold the tuples
	i = 0
	Final_Array = []
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
							redflag = 1          #Checks to see if the word is in ignoreWords list
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
		Final_Array.append(tuple([longarr[i]] + longarr[i+1]))
		i+=2
		Final_Array.sort(key = lambda Final_Array:Final_Array[0][0].lower())
	return Final_Array

import time, cProfile, pstats
from io import StringIO
from time import strftime
with open('Test.txt', 'r') as myfile:
        data=myfile.read()

start = time.time()
profiler = cProfile.Profile()

profiler.enable()
assert kwic(data, periodsToBreaks = False, ignoreWords =[], listPairs = False)
total_time = time.time() - start
profiler.disable()

fo = open("Timetest_log.txt","a+") 
s = StringIO()
sortby = 'cumulative'
ps = pstats.Stats(profiler, stream=s).sort_stats(sortby)
ps.print_stats()
fo.write(strftime("%a,%d %b %Y %H:%M:%S \n"))
fo.write(s.getvalue())
str = input("Enter what you did to change this: ")
fo.write("What was changed in this test: %s" %str)
fo.close()
