#!bin/bash

echo 'Heyo, running BruteForce'

python Bruteforce.py $1

echo 'Done Running BruteForce'

echo 'Moving on to NaiveDnC'

python NaiveDnC.py $1

echo 'Done with NaiveDnC'

echo 'Starting Enhanced version'

python EnhancedDnC.py $1

echo 'All done! Check out the time logs if your interested!'
