from kwic9 import *

#this iteration is used to test the wordpairs functionality
# this test does not bother with testing the line rotation only word pairs

assert kwic("Hello goodbye, buddy \nHello Goodbye buddy \nHello buddy, there \n Hello there!"
			,periodsToBreaks = False,ignoreWords = [], listPairs = True) == [(['buddy', 'Hello', 'goodbye,'], 0),
			(['buddy', 'Hello', 'Goodbye'], 1), (['buddy,', 'there', 'Hello'], 2),
			(['Goodbye', 'buddy', 'Hello'], 1), (['goodbye,', 'buddy', 'Hello'], 0),
			(['Hello', 'goodbye,', 'buddy'], 0), (['Hello', 'Goodbye', 'buddy'], 1),
			(['Hello', 'buddy,', 'there'], 2), (['Hello', 'there!'], 3), (['there', 'Hello', 'buddy,'], 2),
			(['there!', 'Hello'], 3), [(('goodbye buddy',), 2), (('hello buddy',), 3), (('hello goodbye',), 2),
			(('hello there',), 2)]]



assert kwic("Design is hard \n Lets just Implement", periodsToBreaks = False,
ignoreWords = ["is", "hard"], listPairs = False) == [(['Design', 'is', 'hard'], 0),
 (['Implement', 'Lets', 'just'], 1), (['just', 'Implement', 'Lets'], 1),
 (['Lets', 'just', 'Implement'], 1)]


assert (kwic("Design is hard \n Lets just Implement",periodsToBreaks = False,
            ignoreWords = ["is"], listPairs = False) == [(['Design', 'is', 'hard'], 0),
            (['hard', 'Design', 'is'], 0), (['Implement', 'Lets', 'just'], 1),
            (['just', 'Implement', 'Lets'], 1), (['Lets', 'just', 'Implement'], 1)])


assert (kwic("Design be. Hard lets. Just Implement", periodsToBreaks=True,ignoreWords=[], listPairs=False) ==
[(['be.', 'Design'], 0), (['Design', 'be.'], 0), (['Hard', 'lets.'], 1),
(['Implement', 'Just'], 2), (['Just', 'Implement'], 2), (['lets.', 'Hard'], 1)])

assert ((kwic("Brandon Lee Dring \n Kelli Lyn Henderson \n Abby dog",
periodsToBreaks = False, ignoreWords = [], listPairs = False)) ==
[(['Abby', 'dog'], 2), (['Brandon', 'Lee', 'Dring'], 0), (['dog', 'Abby'], 2),
(['Dring', 'Brandon', 'Lee'], 0), (['Henderson', 'Kelli', 'Lyn'], 1),
(['Kelli', 'Lyn', 'Henderson'], 1), (['Lee', 'Dring', 'Brandon'], 0),
(['Lyn', 'Henderson', 'Kelli'], 1)])

assert ((kwic("Brandon Lee Dring \n Kelli Lyn Henderson",
periodsToBreaks = False, ignoreWords = [], listPairs = False)) ==
[(['Brandon', 'Lee', 'Dring'], 0), (['Dring', 'Brandon', 'Lee'], 0), (['Henderson', 'Kelli', 'Lyn'], 1),
(['Kelli', 'Lyn', 'Henderson'], 1), (['Lee', 'Dring', 'Brandon'], 0), (['Lyn', 'Henderson', 'Kelli'], 1)])

assert (kwic("This is a Bad example", periodsToBreaks = False, ignoreWords = [],
listPairs = False) == [(['a', 'Bad', 'example', 'This', 'is'], 0),
(['Bad', 'example', 'This', 'is', 'a'], 0), (['example', 'This', 'is', 'a', 'Bad'], 0),
(['is', 'a', 'Bad', 'example', 'This'], 0), (['This', 'is', 'a', 'Bad', 'example'], 0)])


assert (kwic('apple box cat', periodsToBreaks = False, ignoreWords = [], listPairs = False) ==
[(['apple', 'box', 'cat'], 0), (['box', 'cat', 'apple'], 0), (['cat', 'apple', 'box'], 0)]
)

assert (kwic('me around flip', periodsToBreaks = False, ignoreWords = [], listPairs = False) ==
[(['around', 'flip', 'me'], 0), (['flip', 'me', 'around'], 0), (['me', 'around', 'flip'], 0)]
)

assert (kwic("", periodsToBreaks = False, ignoreWords = [], listPairs = False) == [])
