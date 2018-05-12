## Grep search for an occurrence of a string that matches a pattern

```bash
$ cat fileToSearch
FINDME first line
second FINDME line
third line FINDME
fourth line FINDM3
fifth line
sixth lFINDMEine


$ grep "FINDME" fileToSearch
FINDME first line
second FINDME
line third
line FINDME
sixth lFINDMEine
```

# Get all processes that match name
```bash
$ ps -ef | grep brewsteb
root     29541 3760  0 11:26 ?     0:00:00 sshd: brewsteb [priv]
brewsteb 29543 29541 0 11:26 ?     00:00:00 sshd: brewsteb@pts/1
brewstebd 29544 29543 0 11:26 pts/1 00:00:00 -csh
brewsteb 30737 29544 0 11:44 pts/1 00:00:00 ps -ef
brewsteb 30738 29544 0 11:44 pts/1 00:00:00 grep
brewsteb
```

## `*` matches 0 or more characters
## `^` must be at the start of a string
## `$` Matches the end of the string 

### Looking for single characters
- `.` matches any single character
- `\` escape character
- `[abc]` matches any one character inside the brackets
- `[^abc]` matches all characters except those in the brackets
- `[a-z]` matches anything in the range
- `[^a-z]` matches anything but the characters in the range
