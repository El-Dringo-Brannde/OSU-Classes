from kwic1 import *
# This test is meant to test creating the circular shifts and holding them as tuple arrays
#in a larger array

periodstoBreak = False
listpair = []
ignorewords = False
assert (kwic('me around flip', periodstoBreak, ignorewords, listpair) ==
[('around', 'flip', 'me', 0), ('flip', 'me', 'around', 0), ('me', 'around', 'flip', 0)])
