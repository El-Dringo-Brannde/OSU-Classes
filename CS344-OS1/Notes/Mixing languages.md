# Mixing Languages

### Awk Hello World example:
```awk
\#!/usr/bin/awk -f
BEGIN { print "Hello, world!"; exit }
```
- But kinda depricated now since you can do a good part of awk functionality in bash

- Awk features associative arrays, where anything can map to anything. Sort of like a hash table


### Perl Hello World example:
```Perl
#!/usr/bin/perl # The traditional first program.
# Strict and warnings are recommended.
use strict; use warnings;
# Print a message.
print "Hello, World!\n";
```

##### Don't use perl python is better :)

## Python compared to C, can be up to 53 times slower
- BUT scripting languages and compiled languages can be written together.
- You can intermix compiled and interpreted languages together
- __Such as mixing Python and C__

  - A python program can call a c program
```Python  
$ gcc –o c-billion c-billion.c #<-- just compile it first
$ cat python-billion-fast
#!/usr/bin/python
from subprocess import call call("./c-billion")
$ /usr/bin/time --format='%C took %e seconds' python-billion-fast
python-billion-fast took 2.91 seconds
```

- The only problem is that you can't really have a return value from just a simple C call. You could have the C program write to a file, then read that file back in Python.

- Or you could use a Unix pipe, use the instant module in Python, Python C API, Ctypes etc etc.

-  You could even embed a Python program into C if you like, Playing with strings, or writing to files is much easier in Python than in C 
