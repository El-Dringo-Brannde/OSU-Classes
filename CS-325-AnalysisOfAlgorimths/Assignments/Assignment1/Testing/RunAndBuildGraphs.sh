#!bin/bash
echo 'Hello cruel world'
echo 'testing BruteForce with input files '

rm -f output_bruteforce.txt
rm -f timelog_bruteforce.txt

python BruteForce.py 100.txt
python BruteForce.py 1000.txt
python BruteForce.py 2000.txt
python BruteForce.py 3000.txt
python BruteForce.py 4000.txt
python BruteForce.py 5000.txt
python BruteForce.py 6000.txt
python BruteForce.py 7000.txt
python BruteForce.py 8000.txt
python BruteForce.py 9000.txt
python BruteForce.py 10000.txt

echo 'Done running the BruteForce test.'


echo 'Running NaiveDnC algorithm on files'


rm -f Output.NaiveDnC.txt
rm -f timeLog.NaiveDnC.txt

python NaiveDnC.py 100.txt
python NaiveDnC.py 1000.txt
python NaiveDnC.py 2000.txt
python NaiveDnC.py 3000.txt
python NaiveDnC.py 4000.txt
python NaiveDnC.py 5000.txt
python NaiveDnC.py 6000.txt
python NaiveDnC.py 7000.txt
python NaiveDnC.py 8000.txt
python NaiveDnC.py 9000.txt
python NaiveDnC.py 10000.txt

echo 'Done running tests with NaiveDnC'


echo 'Done running NaiveDnC, Moving on '


rm -f Output.EnhancedDnC.txt
rm -f timeLog.EnhancedDnC.txt


echo 'Running tests on the EnhancedDnC.py'

python EnhancedDnC.py 100.txt
python EnhancedDnC.py 1000.txt
python EnhancedDnC.py 2000.txt
python EnhancedDnC.py 3000.txt
python EnhancedDnC.py 4000.txt
python EnhancedDnC.py 5000.txt
python EnhancedDnC.py 6000.txt
python EnhancedDnC.py 7000.txt
python EnhancedDnC.py 8000.txt
python EnhancedDnC.py 9000.txt
python EnhancedDnC.py 10000.txt

echo 'DONE! Now Creating graph of algorithms'
python PlottingTest.py timelog_bruteforce.txt timeLog.NaiveDnC.txt timeLog.EnhancedDnC.txt

echo 'All done! Peace out!'
