from kwic3FINAL import *

# This test is meant to test the line break feature '/n' where
# anytime there is a line break it stops rotating around that line
# and only does the rotation on one line at a time while also tracking its line position index

periodstoBreak = False
listpair = False
ignorewords = []

assert(kwic("Brandon Lee Dring \n Kelli Lyn Henderson",
periodstoBreak, listpair, ignorewords) ==
[('Brandon', 'Lee', 'Dring', 0), ('Dring', 'Brandon', 'Lee', 0), ('Henderson', 'Kelli', 'Lyn', 1),
('Kelli', 'Lyn', 'Henderson', 1), ('Lee', 'Dring', 'Brandon', 0), ('Lyn', 'Henderson', 'Kelli', 1)])



#	To test against the previous test
#assert (kwic("apple box cat") == [('apple', 'box', 'cat'), ('box', 'cat', 'apple'), ('cat', 'apple', 'box')])
