#!/bin/bash
#By Brandon Dring CS344
arg=$1
linearray=()
rows=0
dataarray=()
columns=0

function readydata(){
 while read -r line
    do
     words=($line) #just gets a single line
	   linearray+=("$line") #appends line to array
     rows=$(($rows+1)) #counts how many rows there are
    done < "$file"

columns=${#words[@]}  #finds the number of columns in txt file
for q in ${linearray[@]}
  do
    dataarray+=($q) #converts array of lines to one fat array of numbers
  done
}

if [[ ${arg:1:1} != 'r' && ${arg:1:1} != 'c' ]]
  then
    echo "Bad user! try again"
    exit 1
elif [ $# -gt 2 ]
  then
  echo "Not today!"
  exit 1
fi


if [ -z $2 ] #Tests to see if there is a second argument
then #if there ISN'T a 2nd argument
  while read line
  do
    columns=$(($columns+1))
    dataarray+=($line)
    rows=$(($rows+1))
  done < /dev/stdin
else
  if test -r $2
  then
    printf "\n"
  else
    echo "I can't read it! :("
    exit 1
  fi
file=./$2
fi



if [ ${arg:1:1} == 'r' ]
then
  if [ $# -eq 2 ]
  then
	 readydata #function call
  fi
i=0
j=0
sum=0
sumarray=()
temparr=()
rows+=$(($rows+1))
for j in ${dataarray[@]}
  do
      temparr+=($j) #temporarily holds a line at a time
      sum=$(($sum+$j))  #holds the running sum of the line
    if test $i -eq $(($columns - 1))  #columns - 1 since it starts at 0
    then
      sumarray+=($sum)  # adds the sum of the line to another array
      IFS=$'\n' sorted=($(sort -n <<<"${temparr[*]}"))   #sorts the array
      size=${#sorted[*]}  #gets the size of the sorted array
      if [ $(( $size%2 )) -eq 0 ]
        then
          sumarray+=(${sorted[ ($size / 2)]}) #if there is no remainder go to middle then right one
        else
          sumarray+=(${sorted[ ($size / 2 )]}) #go to middle of sorted array
      fi
      sorted=()
      temparr=()  #wipes out array
      i=-1  #resets to -1 because we still need it to get to 5 after first line
      sum=0 #clear sum
    fi
    i=$(($i+1)) #increase column counter
  done
printf '\n'
q=0

echo -e "AVERAGE \t MEDIAN"
if [ ${#sumarray[@]} -eq 0 ]
then
  echo -e "Empty Set \t Empty Set"
  exit 0
fi
while [ $q -ne ${#sumarray[@]} ]
  do
    sum=${sumarray[$q]}
    echo -e "$((($sum + $columns / 2) / $columns))  \t\t ${sumarray[$q+1]}"
    q=$(($q+2))
  done

#THIS IS FOR IF THE ARGUEMENT IS FOR COLUMNS INSTEAD
elif [ ${arg:1:1} == 'c' ]
  then
    if [ $# -eq 2 ]
    then
      readydata #function call
    fi
    a=0
    t=0
    sum=0
    temparr=()
    medianarr=()
    while [ $a -ne $columns ] #runs through all the columns of the file
      do
        while [ $t -lt ${#dataarray[@]} ] #runs through each value in file
          do
            temparr+=(${dataarray[t]}) #adds a value from the column
            sum=$(( $sum + ${dataarray[t]} )) #keeps a running sum
            t=$(( $t + $columns))  #goes to the next value in the column
          done
          IFS=$'\n' sorted=($(sort -n <<<"${temparr[*]}"))   #sorts the array
          size=${#sorted[*]}
              if [ $(( $size % 2 )) -eq 0 ] #checks to see if there is an even number of elements
                then
                  medianarr+=(${sorted[$size/2]})
                else
                  medianarr+=(${sorted[$size/2]})
              fi
          temparr=() #wipe array
          sumarray+=($sum) #adds the sum of column to array
          sum=0
          a=$(($a+1))
          t=$(($a)) #goes to next value of the column
    done

  q=0
  echo "AVERAGE:"
  if  [ ${#sumarray[@]} -eq 0 ]
    then
      echo "Empty set"
  fi

  for q in ${sumarray[@]}
  do
    echo -e "$((($q + $rows / 2) /$rows)) \c" #divides the sum by rows in file
    printf "\t"
  done
  printf "\n"

  q=0
  echo "MEDIAN"
  if  [ ${#sumarray[@]} -eq 0 ]
    then
      echo "Empty set"
  fi
  for q in ${medianarr[@]}
  do
    echo -e "$q \c"
    printf "\t"
  done
  printf "\n"

else
  exit 1
fi
