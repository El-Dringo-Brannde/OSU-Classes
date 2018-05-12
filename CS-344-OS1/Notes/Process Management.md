# Process management
#### 'ps' in bash gives processes are running currently

### What is a Zombie?
  - A zombie is a process that terminates and the parent doesn't clean it up
  - A child process must talk to the parent before their resources are released back to the OS
    - If not, the process just lives on forever..

### Orphan Zombies :(
  - If a parent exits without cleaning up children, then it becomes an orphan zombie
  - __Eventually Orphans are adopted by the INIT process which waits for orphans__

### KILL
  - Really the 'kill' command just sends signals
    - e.g. `kill -TERM 1234`

### Job Control
  - Starting a process and retaining control to the command line

### Foreground/Background
  - There can only be one foreground process, to which you interact
  - Processes in the background can still be executing
  - Using CTRL+Z sends a foreground process to background
  - Using `fg %1` or `bg %1` to run things in their respective spaces

##### Who has STDIN/OUT/ERR?
  - Background processes can still write to STDOUT and files

 - Throw a program to the background?
   - Use a `&` in the program name to throw normally a foreground process to the back

### The History command
- `$ history 5`
  - shows the last 5 commands
