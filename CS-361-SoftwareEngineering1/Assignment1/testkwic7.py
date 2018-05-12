from kwic7 import *

# This test is used to alter the ignore word functionality since the kwic7
# program iteration. The functionality works for multiple arguements as well

assert kwic("Design is hard \n Lets just Implement", periodsToBreaks = False,
        ignorewords = ["is", "hard"], listpair = False)
