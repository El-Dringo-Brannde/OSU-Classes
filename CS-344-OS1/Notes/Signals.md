# Signals

## Inter Process Communications
### - Signals
   - They tell a process to do something, via user command or event

### Use of Signals? Process to Process
  - Suspend or resume Execution process
  - Terminate
  - Change modes

## ----------TERMINATION--------------
 Signal | # | Easy Name | Catchable | Meaning | Default | Core Dump
---|---|---|---|---|---|---|
  SIGABRT| 6 |Abort| Yes| Terminate; sent by process itself during abort()call which performs no cleanup, unlike exit().| Terminate| Yes|
  |SIGQUIT| 3| Quit| Yes| Terminate; sent by user.| Terminate|  Yes |
  |SIGINT| 2 |Interrupt| Yes| The process is requested to terminate; performs cleanup; CTRL-C sends this to process and all its children.| Terminate |  No|
  |SIGTERM| 15 |Terminate| Yes| The process is requested to terminate; performs cleanup.| Terminate|  No |
  |SIGKILL| 9|  Kill |No | Terminate instantly, no cleanup; handled entirely by the kernel | not catchable|No|


## -------------_WRONGDOING_-------------
Signal | # | Easy Name | Catchable | Meaning | Default | Core Dump
---|---|---|---|---|---|---|
SIGSEGV| -| Segmentation Fault| Yes|Invalid memory reference; terminate, no cleanup. | Terminate|  Yes|
|SIGBUS |-| Bus Error |Yes| Non-existent physical address. | Terminate |Yes|
|SIGFPE| - | Floating Point Error|  Yes| Sent when a process executes an erroneous floating point or integer operation, such as divide by zero.| Terminate | Yes|
SIGILL| -| Illegal Instruction | Yes | Sent when a process attempts a CPU instruction it cannot issue (malformed, unknown, wrong permissions).| Terminate | Yes|
SIGSYS |-| System Call| Yes| Sent when a process passes an incompatible argument to a system call (rare, we use libraries to do this right for us).|Terminate | Yes|
|SIGPIPE| - |Pipe| Yes| Sent when a process tries to write to a pipe without another process attached to the other end of the pipe.|Terminate |Yes


# ---------------_Control_--------------
Signal | # | Easy Name | Catchable | Meaning | Default | Core Dump
---|---|---|---|---|---|---|
|SIGALRM| 14 |Alarm |Yes| Sent by alarm() function, normally sent & caught to execute actions at a specific time; performs cleanup| Terminate| No|
|SIGSTOP| -| Stop| No|Stop execution (but stay alive). | Stop, not catchable| - |
SIGTSTP| -| Terminal Stop | Yes | Stop execution (but stay alive).| Stop| - |
SIGCONT | - | Continue | Yes | Continue (resume) execution if stopped. | Continue | - |
SIGHUP | 1 | Hang Up | Yes| Sent to a process when its terminal terminates | Terminate|  No |
SIGTRAP | - |  Trap | Yes | Sent when a trap occurs for debugging, i.e. var value change, function start, etc.; terminate, no cleanup. | Terminate |  Yes

## Timers in UNIX
  - Calling `alarm()` in a program
    - waits a specific amount of time then sends the SIGALRM signal
  - What about `sleep()`?
    - `sleep()` calls `alarm()` then calls `pause()`
      - When SIGALRM is received it returns from `sleep()`

## ------------_Child Process Terminated_----------------
Signal | # | Easy Name | Catchable | Meaning | Default | Core Dump
---|---|---|---|---|---|---|
SIGCHLD| -| Child Terminated| Yes| A foreground or background child process of this process has terminated, stopped, or continued.| None| -|
### SIGCHLD allows the parent process to do work instead of going to sleep and waiting on the child
  When it is finally caught it can trigger a wait to clean up the child

## ----------_USER DEFINED SIGNALS_---------------------
Signal | # | Easy Name | Catchable | Meaning | Default | Core Dump
---|---|---|---|---|---|---|
SIGUSR1| - |User 1 | Yes| Has no particular meaning, performs cleanup.|Terminate |No
SIGUSR2| -| User 2| Yes| Has no particular meaning, performs cleanup.| Terminate |No

### Both of these signals is up to the programmer to determine what they do

## Core dumps
  - Come from when memory was stored on magnetic cores
    - reading the memory destroys the memory that was in the core

### Signals received by your program will carry out their default action
  - ##### But you can over ride them with your own signal handling functions

## Use `pause()` instead of `sleep()`, pause allows the program to still respond to signals

### `Raise()` and `alarm()`
  - You can send yourself signals with `raise()`
  - Alarm sends a signal after a X amount of seconds
 - You can only have one alarm active at a `time()`

## Creating your own signal handling functions
`int sigaction(int signo, struct sigaction *newact, struct sigaction *origact);`
## The sigaction struct
```C
struct sigaction {
  void (*sa_handler)(int); // name of function to run
  sigset_t sa_mask; // what signal to block while executing
  int sa_flags; // sigaction flags
  void (*sa_sigaction)(int, siginfo_t*, void*); // alternative function handler
};
```
## Catching and rewriting signals
```C
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
void catchSIGINT(int signo) {
char* message = "Caught SIGINT, sleeping for 5 seconds\n";
write(STDOUT_FILENO, message, 38);
raise(SIGUSR2);
sleep(5);
}

void catchSIGUSR2(int signo) {
char* message = "Caught SIGUSR2, exiting!\n";
write(STDOUT_FILENO, message, 25);
exit(0);
}

main() {
struct sigaction SIGINT_action, SIGUSR2_action, ignore_action;

SIGINT_action.sa_handler = catchSIGINT;
sigfillset(&SIGINT_action.sa_mask);
SIGINT_action.sa_flags = 0;
SIGUSR2_action.sa_handler = catchSIGUSR2;
sigfillset(&SIGUSR2_action.sa_mask);
SIGUSR2_action.sa_flags = 0;
ignore_action.sa_handler = SIG_IGN;
sigaction(SIGINT, &SIGINT_action, NULL);
sigaction(SIGUSR2, &SIGUSR2_action, NULL);
sigaction(SIGTERM, &ignore_action, NULL);
sigaction(SIGHUP, &ignore_action, NULL);
sigaction(SIGQUIT, &ignore_action, NULL);

printf("SIGTERM, SIGHUP, and SIGQUIT are disabled.\n"); printf("Send a SIGUSR2 signal to kill this program.\n"); printf("Send a SIGINT signal to sleep 5 seconds, then kill this program.\n");

while(1)
  pause();
}
```
## When you create a child process, it receives all the signal handlers from the parent
-   But if you were to call `exec()`, it removes all special signal handling functions


# No signal is truly blocked it will still be there, just wait til after it is unblocked
