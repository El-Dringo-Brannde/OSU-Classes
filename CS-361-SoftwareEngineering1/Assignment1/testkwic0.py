
from kwic0 import *
#This test just makes sure that I can get to my kwic function in the other file
#and that my test function can handle the empty case.

periodstoBreak = False
ignorewords = []
listpair = False
assert (kwic("", periodstoBreak, ignorewords, listpair) == [])
