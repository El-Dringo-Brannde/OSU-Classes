from kwic4 import *

periodsToBreaks = True
listpair = False
ignorewords = []

#this version is used to test periods to breaks feature, such that a lowercase
#letter followed by a '.' then a capital letter is essentially a line break

assert (kwic("Design is hard", periodsToBreaks,ignorewords, listpair))
