Authors: Brandon Dring & Alec Zitzelberger



To run the programs you can either use a script I provided called
RunAllAlgorithms.sh it takes an argument which is the file you want to read.
It applies this argument to each of the different versions of the algorithm.

------------------------------------------------------------------------------

So for example to run it you would type

bash RunAllAlgorithms.sh <Your File Here>

------------------------------------------------------------------------------

I've used the input files for everything along with txt files I've generated,
anything else I'm not sure of

Or you could just do it the manual way and go

python <Version of algorithm> <File to read>

------------------------------------------------------------------------------

Testing Conditions:

I built this with my Macbook Pro, its running on Mac OSX 10.12.2. To test the time I started a timer
before the program ran and ended it write before it starts writing data to files as that is not
part of the algorithm we are looking at. I also ran this on the school server
to make sure everything works like it is supposed to which it does.
It should be runnable with python2.7. To record any of the times and plot them, I used my computer
with no processes running as opposed to the school server which may have hundreds of people on it
at once.

I used an random number generator to build a txt file of points to test on. Along with whatever
test files were provided via canvas, it works with floats too, I'm not sure about negatives, but
I think python would handle that just fine.
