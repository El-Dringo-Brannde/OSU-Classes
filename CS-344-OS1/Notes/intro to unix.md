# Intro to Unix

### Unix 1965
  - AT&T, MIT, and GE jointly develop Multics, provides hierarchical file system

### Unix in 1969
  - AT&T pulls out, but their researches continue on their own
    - Dennis Ritchie and Ken Thompson create UNIX

### Unix 1970
  - Time zero starts at Jan, 1 1970
  - Text processing abilities render it useful in other departments

### Unix in the 70's
  - in 1972 UNIX is rewritten in C
  - Presented to the world in 1973, anti-trust regulations prevented it from being a product

### Linux
  - Initially developed to be a Unix-like but not held down with licenses to AT&T
  - Open source
  - Stable, robust, and free Released on March 14, 1994

### Computer Architecture TLDR
  - Hardware performs tasks fed to it by the OS
  - The KERNAL, provides the scheduler, which distributes CPU time

### What is a shell?
  - A command line based interface to the Operating system
  - Provides access to all UNIX user-level programs
    - Start programs
    - Manage processes(Job control)
    - Connect programs (Pipes)
    - Kill programs

## Shell Examples
  `ls -a`
    *lists all files (hidden too)*

### Different UNIX shells
  - Bourne Shell `/bin/sh`
  - Bourne again Shell `/usr/local/bin/bash`

### Unix commands
  `alias`
   - creates a shortcut for running a program
    ex: `$ alias l = "ls -pla --color=auto" `

### Standard files and the Terminal
  - shell automatically opens the terminal for reading with one file, and writing for 2 (stdout, and stderr)
  - __by default it goes back to the prompt unless redirected__

### Redirecting stdout
  - The `>` operator tells stdout to open a different file for writing to
  - ex: `$ echo -e "fart\npoop" > random`
    - Says put the contents of this echo into a file called random
### Common UNIX commands
  - `Sort`
    - Takes data from stdin OR a file, and sends the data, alphabetically to stdout

### Redirecting stdin
  - `<` redirects stdin to operate on a different file from reading
    - ex: `$ sort < random`  <-- dumps random into stdin, which is then tossed to sort

### stdin with no redirection
- `$ cat > list`
  ^ Here stdin hasn't been changed, just stdout, so data comes indefinetly
       from the keyboard until cancelled and afterwards dumps it to list

## Redirecting both stdin and stdout
  - `$ echo -e "apple\nbox\ncat" > foodlist`
  - `$ sort < foodlist > sortedfood`
    - __So we read from left to right, sort gets opened up with input coming__
        - from foodlist, then the sorted foodlist gets written to sortedfood

### Shell File name expansion
  - some characters are replaced with all files with matching names
    - \* - matches everything
    - ? - matches character

## Pipes
  - Provides way to communicate commands without using temp data
    - ex: `$ echo -e "fart\ncat\ndog" | sort`
             ^ dumps string into sort
  - ULTIMATELY a pipe connects the stdout of a command and connects it to the stdin of another command

- `>>` operator appends stdout to the end of a file
