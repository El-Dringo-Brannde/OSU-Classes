from kwic2 import *

#this test is meant to alphabetize the large array that is spit out at
#the end which holds the miniature array for each rotation
periodstoBreak = False
listpair = False
ignorewords = []
assert (kwic("apple box cat", periodstoBreak, listpair, ignorewords) ==
[('apple', 'box', 'cat', 0), ('box', 'cat', 'apple', 0), ('cat', 'apple', 'box', 0)])

#assert (kwic('me around flip') ==
#[('around', 'flip', 'me'),('flip', 'me', 'around'),('me', 'around', 'flip')])
