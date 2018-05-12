import eventspec
es = eventspec.EventSpec("kwic.fsm")


class kwic():

    def __init__(self, periodsToBreaks=None, ignoreWords=None, doc=None):
        if periodsToBreaks == None:
            periodsToBreaks = False
        if ignoreWords == None:
            ignoreWords = [""]

        self.periodsToBreaks = periodsToBreaks
        self.ignoreWords = ignoreWords
        self.document = ""
        es.event("callConstructor")

    def addText(self, doc):
        self.document += doc
        es.event("callAddText")

    def index(self):
        es.event("callIndex")
        if self.document:
            es.event("callDocument")
            Final_Array, Unsplit_lines, Parsed_Array = ([] for i in range(3))
            if (self.periodsToBreaks == True):  # If there are periods to breaks w/o listpairs
                line_by_period = self.document.split(". ")
                Final_Array = Parse_document(line_by_period, self.ignoreWords)

            elif ("\n" in self.document):  # checks to see if there is a line break to iterate through
                # splits the two strings by the \n character
                Comp_line = self.document.splitlines()
                Final_Array = Parse_document(Comp_line, self.ignoreWords)

            else:  # If there are no line splits go here
                Parsed_line, longarr = ([] for i in range(2))
                Parsed_line.append(self.document.split())
                Parsed_line.append([0])
                Rotate_Lines(Parsed_line, self.ignoreWords, longarr)
                longarr = [list(i) for i in longarr]
                i = 0
                while (i != int(len(longarr))):
                    Final_Array.append(tuple([longarr[i]] + longarr[i + 1]))
                    i += 2
                Final_Array.sort(key=lambda x: list(map(str.lower, x[0])))

            return Final_Array
        else:
            es.event("callNoDoc")
            empty_list = []
            return empty_list

    def listPairs(self):
        es.event("callListPairs")
        Final_Array, Unsplit_lines, Parsed_Array = ([] for i in range(3))
        if self.periodsToBreaks == True:
            Unsplit_lines = self.document.split(". ")
            line_by_period = [x.split() for x in Unsplit_lines]
            Processed_pairs = proc_linepairs(
                line_by_period, Final_Array, self.periodsToBreaks)
        elif self.periodsToBreaks == False:
            Parsed_Array = self.document.splitlines()
            unspitlines = Parsed_Array[:]
            Parsed_Array = [x.split() for x in Parsed_Array]
            Processed_pairs = proc_linepairs(
                Parsed_Array, Final_Array, self.periodsToBreaks)
        return Processed_pairs

    def reset(self):
        self.document = ""
        es.event("callReset")


def Remove_Punctuation(Parsed_Array):
    es.event("callRemovePunct")
    for b in (range(len(Parsed_Array))):
        for c in (range(len(Parsed_Array[b]))):
            d = 0
            # Removes any puncuation in the strings
            while d != len(Parsed_Array[b][c]):
                letter = Parsed_Array[b][c][d]
                if (letter == chr(33) or letter == chr(46) or letter == chr(63) or letter == chr(44) or letter == chr(58)):
                    Parsed_Array[b][c] = Parsed_Array[b][c][:d]
                else:
                    d += 1


def Find_WordPairs(Parsed_Array, wordpairs):
    es.event("FindWP")
    for i in range(len(Parsed_Array) - 1):  # goes the number of lines
        # goes the number of words in line
        for f in range(len(Parsed_Array[i]) - 1):
            spot1 = Parsed_Array[i][f]
            t = f + 1  # prevents from checking before spot1
            while t != int(len(Parsed_Array[i])):  # goes to length of line
                spot2 = Parsed_Array[i][t]  # grabs the second word
                q = i + 1  # prevents going back before the current string iteration
                while q != len(Parsed_Array):  # goes length from where next line is to end
                    # goes the number of words in next line
                    for x in range(len(Parsed_Array[q])):
                        check1 = Parsed_Array[q][x]
                        if (spot1 == check1 or spot2 == check1):
                            w = x + 1  # prevents check2 from starting back over in string
                            # repeats while the end of the line hasn't been hit
                            while w != len(Parsed_Array[q]):
                                check2 = Parsed_Array[q][w]
                                if (spot1 == check1 or spot1 == check2) and (spot2 == check2 or spot2 == check1) and (spot1 != spot2):
                                    pair = spot1 + " " + spot2
                                    wordpairs[pair] = wordpairs.setdefault(
                                        pair, 0) + 1
                                w += 1
                    q += 1
                t += 1

# Requires format of [['this', 'a','sentence'], '...']


def proc_linepairs(Parsed_Array, Final_Array, periodsToBreaks):
    Parsed_Array = [[str.lower(i) for i in j] for j in Parsed_Array]
    Remove_Punctuation(Parsed_Array)
    wordpairs = dict()
    Final_Word_Pairs, holder = ([] for i in range(2))
    Find_WordPairs(Parsed_Array, wordpairs)
    for key, value in wordpairs.items():
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
            Final_Word_Pairs.append(
                tuple([tuple(holder[i])]) + tuple([holder[i + 1]]))  # Formatting
        i += 2
    Final_Word_Pairs.sort()
    return Final_Word_Pairs


def Rotate_Lines(Parsed_line, ignoreWords, longarr):
    es.event("callRotator")
    i = 0
    while i != int(len(Parsed_line)):
        for j in range(len(Parsed_line[i])):
            front = Parsed_line[i].pop(0)
            Parsed_line[i].insert(len(Parsed_line[i]), front)
            if len(ignoreWords) != 0:
                redflag = 0
                for q in range(len(ignoreWords)):
                    if Parsed_line[i][0] == ignoreWords[q]:
                        redflag = 1  # Checks to see if the word is in ignoreWords list
                if redflag != 1:
                    longarr.append(tuple(Parsed_line[i]))
                    longarr.append(tuple(Parsed_line[i + 1]))
            else:
                longarr.append(tuple(Parsed_line[i]))
                longarr.append(tuple(Parsed_line[i + 1]))
        i += 2


def Parse_document(Comp_line, ignoreWords):
    es.event("callParser")
    Parsed_line, Index_Tracker, Final_Array, longarr = ([] for i in range(4))
    for i in (range(len(Comp_line))):  # runs the length of the lines given
        # break the words of each line into own array piece
        Parsed_line.append(Comp_line[i].split())
        Index_Tracker.append(i)
        d = Index_Tracker[:]
        while (len(d) != 1):
            d.pop(0)
        Parsed_line.append(d)
    Rotate_Lines(Parsed_line, ignoreWords, longarr)
    longarr = [list(i) for i in longarr]
    i = 0
    while (i != int(len(longarr))):
        Final_Array.append(tuple([longarr[i]] + longarr[i + 1]))
        i += 2
    Final_Array.sort(key=lambda x: list(map(str.lower, x[0])))
    return Final_Array
