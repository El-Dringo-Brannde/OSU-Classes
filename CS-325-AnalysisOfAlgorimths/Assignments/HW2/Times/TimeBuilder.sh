#!/bin/bash

for i in {1..5}
do
  python Align.py input500.txt
done

python Normalize.py
rm -f timeLog.txt

for i in {1..5}
do
  python Align.py input1000.txt
done

python Normalize.py
rm -f timeLog.txt

for i in {1..5}
do
  python Align.py input2000.txt
done

python Normalize.py
rm -f timeLog.txt


for i in {1..5}
do
  python Align.py input3000.txt
done

python Normalize.py
rm -f timeLog.txt


for i in {1..5}
do
  python Align.py input4000.txt
done

python Normalize.py
rm -f timeLog.txt


for i in {1..5}
do
  python Align.py input5000.txt
done

python Normalize.py
rm -f timeLog.txt
