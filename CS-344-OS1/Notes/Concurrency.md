# Concurrency

## UNIX supports concurrency, part of why its so fast

### System call
  - interrupts a program process, tosses control to OS
    - Waits until system call returns

### Multiprogramming
  - Multiple processes can be ready to execute
  - System calls trigger context switches, next process runs

### Time sharing
  - CPU splits time between multiple processes

### Race conditions
  - Order of things happen incorrectly

### Access Control
  - Only one process may hold the lock to the resource they want
  - Can be controlled with software as well

## Kernel
  - Manages Hardware/drivers
  - Scheduler
  - Scheduler
    - Prioritizes CPU time

### Threads > Processes
  - Threads share data
    - Have their own stack, and can access stacks of other threads
  - CPU switches back and forth faster between threads than processes

## Threads
  - Kernel level
    - Controlled by kernel, and scheduler
  - User level
    - Don't involve the kernel ever
    - Emulates threading
    - Can be really fast since you're not switching anything really
    - Can be blocked by the system or scheduler


## Thread implementation in UNIX
  ``#include <pthread.h>``

  - compile with ``-lpthread`` option in gcc
  `void*` means a pointer.. to something or anything




## Creating a thread
```c
int result ;
pthread_t mythreadid;

result = pthread_create(&mythreadid, NULL, start_routine, NULL);
```
- threads can be killed by various commands i.e:
  - thread calling `pthread_exit()`
  - returns from `start_routine()`
  - by another thread `pthread_cancel()`


## Mutexes
  - kinda like locks for software induced threads
