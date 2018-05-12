from kwic5 import *

periodsToBreaks = False
ignorewords = ["is"]
listpair = False
# This test is used to make sure that the ignorewords function works 
assert kwic("Design is hard \n Lets just Implement",periodsToBreaks,
            ignorewords, listpair)
