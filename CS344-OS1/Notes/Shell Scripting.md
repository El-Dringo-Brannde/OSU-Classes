# Shell Scripting
  - ex:
    ```bash
    #!/bin/bash <-- tells unix the interpreter to use for the script
       #Comment
       echo "Hello World!"
       Variables
       myint=1
       myvar=Ben
    ```
    - Access variables with `$` infront of variable name
      - ex:
      ```bash
        myint=1
        echo $myint
      ```
    - Single quotes (' ')
      - Doesn't expand the variables inside the ticks
    - Double quotes ("")
      - Expands variables

#### __Don't forget dos2unix to correct any line spacing errors__

## Special parameters
  - `$` - The process ID of the script itself running
  - `?` - The return value of the previous running script
  - `#` - optional arguments given when script is executed
  - `exit` command returns result to '?' parameter

### if statements
```bash
    if ....
    then
      ...
    elif ...
    then
      ...
    else
    then
      ....
  fi <-- close statements
```


## Error handling
  - `#!/bin/bash -e` <-- adding the -e makes sure it will only continue if everything returns 0
  - `cp word.docx newdoc.docx`
  - `rm -f word.docx`

### For loop syntax
```bash
  #!/bin/bash
  for i in a b c d
  do
    printf "<%s>" $i
  done
```
### While loop syntax
```bash
  #!/bin/bash
  i = 0
  while test $i -ne 2
  do
    printf "i = $i \n"
    i = $(expr $i + 1)
  done
printf "i = $i"
```

## Sub shells
  - Some operators like ``=`` require strings or numbers, not variables themselves
  - If you want to alter a variable it has to be ran in its own subshell and be returned
  - ex: to increment a variable
    - i = $(expr $i = 1)
      - grabs the result from stdout in subshell
    - `i=$(($i+1))` does math directly and doesnt need expr


### Loop over an array
```bash
  #!/bin/bash
  array = (one two three)
  for i in "${array[@]}"
  do
    echo $i
  done
```
### sumloop
```bash
  #!/bin/bash
  sum=0
  $file=./testfile
  echo -e "8\n7\n6" > $file
  while read num
  do
    sum=$(($sum+$num))
    echo "$sum"
  done < $file #<--- Here we are pushing the file declared above to be read
```
