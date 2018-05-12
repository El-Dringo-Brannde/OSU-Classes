from threading import Thread
class ThreadWithReturnValue(Thread):
    def __init__(self, group=None, target=None, name=None, args=(), kwargs=None, *, daemon=None):
        Thread.__init__(self, group, target, name, args, kwargs, daemon=daemon)

        self._return = None

    def run(self):
        if self._target is not None:
             self._return = self._target(*self._args, **self._kwargs)

    def join(self):
        Thread.join(self)
        return self._return

def kwic(doc, periodsToBreaks, ignoreWords, listPairs):
	if doc:
		Final_Array,Unsplit_lines,Parsed_Array = ([] for i in range(3))
		if listPairs == True and periodsToBreaks == True:
			Unsplit_lines = Proccess_Periods(doc)
			line_by_period = [x.split() for x in Unsplit_lines]
			Processed_pairs = ThreadWithReturnValue(target =proc_linepairs, args = (line_by_period,Final_Array,periodsToBreaks))
			Processed_pairs.start()
			Threaded_Final_Array = ThreadWithReturnValue(target = Parse_document,args = (Unsplit_lines,ignoreWords, ))
			Threaded_Final_Array.start()
			Final_Array = [Threaded_Final_Array.join()]
			Final_Array.append(Processed_pairs.join())

		elif listPairs and not periodsToBreaks:
			Parsed_Array = doc.splitlines()
			unspitlines = Parsed_Array[:]
			Parsed_Array =[x.split() for x in Parsed_Array]
			Processed_pairs = ThreadWithReturnValue(target = proc_linepairs, args = (Parsed_Array,Final_Array,periodsToBreaks, ))
			Processed_pairs.start()
			Threaded_Final_Array = ThreadWithReturnValue(target = Parse_document,args = (unspitlines,ignoreWords, ))
			Threaded_Final_Array.start()
			Final_Array = [Final_Array.join()]
			Final_Array.append(Processed_pairs.join())

		elif periodsToBreaks:  #If there are periods to breaks w/o listpairs
			line_by_period = Proccess_Periods(doc)
			Final_Array = Parse_document(line_by_period, ignoreWords)

		elif "\n" in doc: #checks to see if there is a line break to iterate through
			Comp_line = doc.splitlines() #splits the two strings by the \n character
			Final_Array = Parse_document(Comp_line, ignoreWords)

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
	for i in range(len(doc)):
		astring+=doc[i]
		if ((doc[i-1] >= chr(97) and doc[i-1] <= chr(122)) #test between lowercase characters
		and doc[i] == '.' and doc[i+1] == ' '):	#test for '.' and ' ' after period
			line_by_period.append(astring)
			astring = ""
	line_by_period.append(astring)
	return line_by_period

def Remove_Punctuation(Parsed_Array):
	for b in (range(len(Parsed_Array))):
		for c in (range(len(Parsed_Array[b]))):
			d = 0
			while d != len(Parsed_Array[b][c]): #Removes any puncuation in the strings
				letter = Parsed_Array[b][c][d]
				if (letter == chr(33) or letter == chr(46) or letter == chr(63) or letter == chr(44) or letter == chr(58)):
					Parsed_Array[b][c] = Parsed_Array[b][c][:d]
				else:
					d +=1

def Find_WordPairs(Parsed_Array,wordpairs):
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
									pair = spot1 + " " + spot2
									wordpairs[pair] = wordpairs.setdefault(pair,0) + 1
								w +=1
					q += 1
				t += 1

# Requires format of [['this', 'a','sentence'], '...']
def proc_linepairs(Parsed_Array,Final_Array,periodsToBreaks):
	Parsed_Array = [[str.lower(i) for i in j] for j in Parsed_Array]
	Remove_Punctuation(Parsed_Array)
	wordpairs = dict()
	Final_Word_Pairs,holder = ([] for i in range(2))
	greenflag = 1
	Find_WordPairs(Parsed_Array,wordpairs)
	for key,value in wordpairs.items():
		wordcount = wordpairs[key]
		if wordcount == 1:
			wordcount += 1
		holder.append(key)
		holder.append(wordcount)
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
	Final_Array, temparr = ([] for i in range(2))
	Zero_Line_Index = [0]
	for i in (range(len(Comp_line[0]))):
		front = Comp_line[0].pop(0)
		Comp_line[0].append(front)
		if len(ignoreWords) != 0:
			for q in range(len(ignoreWords)):
				if b[0] != ignoreWords[q]:
					temparr.append(tuple(Comp_line))
					temparr.append(Zero_Line_Index)
		temparr.append(tuple(Comp_line[0]))
		temparr.append(Zero_Line_Index)
	temparr = [list(i) for i in temparr]
	q = 0
	while (q != int(len(temparr))):
		Final_Array.append(tuple(temparr[q]+temparr[q + 1]))
		q += 2
	Final_Array.sort(key=lambda x: list(map(str.lower, x[0])))#Sorts case insensitive
	return Final_Array


def Parse_document(Comp_line,ignoreWords):
	Parsed_line, Index_Tracker, Final_Array, longarr = ([] for i in range(4))
	for i in (range(len(Comp_line))): #runs the length of the lines given
		Parsed_line.append(Comp_line[i].split())	#break the words of each line into own array piece
		Index_Tracker.append(i)
		d = Index_Tracker[:]
		while (len(d) != 1):
			d.pop(0)
		Parsed_line.append(d)
	i = 0
	while i != int(len(Parsed_line)):
		for j in range(len(Parsed_line[i])):
				front = Parsed_line[i].pop(0)
				Parsed_line[i].insert(len(Parsed_line[i]), front)
				if len(ignoreWords) != 0:
					redflag = 0
					for q in range(len(ignoreWords)):
						if Parsed_line[i][0] == ignoreWords[q]:
							redflag = 1          #Checks to see if the word is in ignoreWords list
					if redflag != 1:
						longarr.append(tuple(Parsed_line[i]))
						longarr.append(tuple(Parsed_line[i + 1]))
				longarr.append(tuple(Parsed_line[i]))
				longarr.append(tuple(Parsed_line[i + 1]))
		i += 2
	longarr = [list(i) for i in longarr]
	i = 0
	while (i != int(len(longarr))):
		Final_Array.append(tuple([longarr[i]] + longarr[i+1]))
		i+=2
	Final_Array.sort(key=lambda x: list(map(str.lower, x[0])))
	return Final_Array
