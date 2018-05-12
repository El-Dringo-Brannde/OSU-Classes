# Processes

## UNIX process components
  - pid
  - Virtual address space
  - user/group identity
  - __A user environment all to its own unlike a thread__

#### Programs vs processes
  - program
    - executable code
  - process
    - running instance of program

### Process states in UNIX
  -  running
  -  waiting/blocked
  -  runnable, waiting on cpu
  -  zombie, waiting to be cleaned up

### Create a process?
  - Unix has an API for this!
    - `fork()`
    - `exec()`

## How to start a new process?
  - `fork()`
  - ProcA is almost the same as ProcB but both get different pids
  - ProcB has copies of all file descriptors, and copies of variables in process A
  - But they are seperately managed
```C
      $ cat forktest.c
      #include <sys/types.h>
      #include <unistd.h>
      #include <stdio.h>
      #include <stdlib.h>

      void main() {
      pid_t spawnpid = -5; int ten = 10;
      spawnpid = fork();
      switch (spawnpid) {
      case -1:
      perror("Hull Breach!"); exit(1);
      break;
      case 0:
      ten = ten + 1;
      printf("I am the child! ten = %d\n", ten);
      break;
      default:
      ten = ten - 1;
      printf("I am the parent! ten = %d\n", ten);
       break;
       }
        printf("This will be executed by both of us!\n");
      }
```
```bash
      $ forktest
      RESULT:
      I am the child! ten = 11
      This will be executed by both of us!
      I am the parent! ten = 9
      This will be executed by both of us!
```

- So if you capture the successful run of a fork you can have it run its own section of the program then break before it gets to anything else

## Items that are inherited by the child
  - code
  - virtual memory
  - signal handling
  - Current working Directory

## Unique to the child
  - ProcID
  - copy of file descriptor
  - pending signals
#### A child process that seg faults does not kill the parent

### Waiting for child process/Terminating children
  - `wait()` will block until any child process dies
  - `waitpid()` blocks until the pid of the child returns

## What if you want to run a totally different program?
  - `exec()`
    - replaces current program with new program specified
      - They don't return
    - If you want to pass arguments to exec, then they are command line arguments
  - `exexl()` and `execv()` don't have the PATH variable must pass as CLA
    - use getcwd() and chdir()

# If you use `fork()` and `exec()` you can keep the original program going and spawn the new program

- End execlp calls with NULL to specify to program that there is no more arguments
