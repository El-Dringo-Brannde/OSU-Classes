## Open File Inheritance
- Files are open and accessible to children forks and execs
- They also share the same file pointers
## Sharing File pointers
```C
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
void main() {
  pid_t forkPID;
  int childExitMethod;
  int fileDescriptor;
char *newFilePath = "./newFile.txt";
 char readBuffer[8];
  memset(readBuffer, '\0', sizeof(readBuffer));
  printf("PARENT: Opening file.\n");
  fileDescriptor = open(newFilePath, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); if (fileDescriptor == -1) {
     printf("Hull breach - open() failed on \"%s\"\n", newFilePath); exit(1);
 }
printf("PARENT: Writing 01234 to file.\n"); write(fileDescriptor, "01234", 5); printf("PARENT: New FP position (all FP positions are zero-indexed): %d\n", lseek(fileDescriptor, 0, SEEK_CUR));
fflush(stdout);
printf("PARENT: Spawning child.\n");
forkPID = fork();
switch (forkPID) {
  case -1: perror("Hull Breach!"); exit(1); break; case 0:
  printf("CHILD: Writing C to file.\n");
  fflush(stdout); write(fileDescriptor, "C", 1);
  printf("CHILD: After write, new FP position: %d\n", lseek(fileDescriptor, 0, SEEK_CUR));
  fflush(stdout);
  printf("CHILD: lseek back 3 chars.\n");
  fflush(stdout);
  printf("CHILD: New FP position: %d\n", lseek(fileDescriptor, -3, SEEK_CUR));
  fflush(stdout);
  printf("CHILD: Reading char.\n");
  fflush(stdout);
  read(fileDescriptor, &readBuffer, 1);
  printf("CHILD: After read, new FP position: %d, char read was: %c\n", lseek(fileDescriptor, 0, SEEK_CUR), readBuffer[0]);
  fflush(stdout); break; default: printf("PARENT: Writing P to file.\n"); fflush(stdout);
  write(fileDescriptor, "P", 1);
  printf("PARENT: After write, new FP position: %d\n", lseek(fileDescriptor, 0, SEEK_CUR));
  fflush(stdout);
  printf("PARENT: lseek back 3 chars.\n");
  fflush(stdout);
  printf("PARENT: New FP position: %d\n", lseek(fileDescriptor, -3, SEEK_CUR));
  fflush(stdout);
  printf("PARENT: Reading char.\n");
  fflush(stdout);
  read(fileDescriptor, &readBuffer, 1);
  printf("PARENT: After read, new FP position: %d, char read was: %c\n", lseek(fileDescriptor, 0, SEEK_CUR), readBuffer[0]);
  fflush(stdout);
  waitpid(forkPID, &childExitMethod, 0);
  lseek(fileDescriptor, 0, SEEK_SET);
  read(fileDescriptor, &readBuffer, 7);
  printf("PARENT: child terminated; file contents: %s\n", readBuffer);
  fflush(stdout);
  break;
  }
}


RESULTS
PARENT: Opening file.
PARENT: Writing 01234 to file.
PARENT: New FP position (all FP positions are zero-indexed): 5
PARENT: Spawning child.
PARENT: Writing P to file.
PARENT: After write, new FP position: 6
PARENT: lseek back 3 chars.
PARENT: New FP position: 3
PARENT: Reading char.
PARENT: After read, new FP position: 4, char read was: 3
CHILD: Writing C to file.
CHILD: After write, new FP position: 5
CHILD: lseek back 3 chars.
CHILD: New FP position: 2
CHILD: Reading char.
CHILD: After read, new FP position: 3, char read was: 2
PARENT: child terminated; file contents: 0123CP
```
## Redirecting data streams using C
- Use `Dup2()` to change in,out,and error to whatever you want

```C
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
int sourceFD, targetFD, result;
if (argc != 3) {
  printf("Usage: sortViaFiles <input filename> <output filename>\n");
   exit(1);
}
sourceFD = open(argv[1], O_RDONLY); if (sourceFD == -1) { perror("source open()");
 exit(1);
 }
 printf("sourceFD == %d\n", sourceFD);// Written to terminal
targetFD = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (targetFD == -1) {
   perror("target open()"); exit(1);
 }
 printf("targetFD == %d\n", targetFD); // Written to terminal
result = dup2(sourceFD, 0); if (result == -1) { perror("source dup2()");
 exit(2);
}
result = dup2(targetFD, 1);
if (result == -1) {
  perror("target dup2()");
  exit(2);
}
execlp("sort", "sort", NULL); return(3);
}
```
# Real inter-process communication (IPC)
- Intermediate/Temporary files
  - Used together with I/O Redirecting
- Pipes
  - IPC b/w two processes forked by common ancestor
- FIFO
  - Named Pipes: B/w two processes on same machine
- Sockets
  - Communication between 2 processes that could be seperated by a network

### Pipes
- The `pipe()` is passed two two integers
  - These are the file descriptors
  - First is input second is output
- `read()` Reads data from the pipe
  - If data is not available it will turn into a BLOCKING CALL
- `write()` writes data into pipe
  - also a BLOCKING CALL

# Pipe Example
```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
void main() {
  int r, pipeFDs[2];
  char completeMessage[512], readBuffer[10];
  pid_t spawnpid;
  if (pipe(pipeFDs) == -1) { perror("Hull Breach!");
  exit(1); } // Create the pipe with error check
spawnpid = fork(); // Fork the child, which will write into the pipe switch (spawnpid) {
  case 0: // Child
  close(pipeFDs[0]); // close the input file descriptor
  write(pipeFDs[1], "CHILD: Hi parent!@@", 19); // Write the entire string into the pipe
  exit(0); break; // Terminate the child
default: // Parent
  close(pipeFDs[1]); // close output file descriptor
  memset(completeMessage, '\0', sizeof(completeMessage)); // Clear the buffer
while (strstr(completeMessage, "@@") == NULL) // As long as we haven't found the terminal...
{
  memset(readBuffer, '\0', sizeof(readBuffer)); // Clear the buffer
  r = read(pipeFDs[0], readBuffer, sizeof(readBuffer) - 1); // Get the next chunk
  strcat(completeMessage, readBuffer); // Add that chunk to what we have so far
  printf("PARENT: Message received from child: \"%s\", total: \"%s\"\n", readBuffer, completeMessage);
  if (r == -1) { printf("r == -1\n"); break; } // Check for errors
  if (r == 0) { printf("r == 0\n"); break; }
}
  int terminalLocation = strstr(completeMessage, "@@") - completeMessage; // Where is the terminal
  completeMessage[terminalLocation] = '\0'; // End the string early to wipe out the terminal
  printf("PARENT: Complete string: \"%s\"\n", completeMessage);
  break;
  }
}
```


## Checking return values of `Read()` and `Write()`
- Both will tell you if there was an error (-1)
- And on success how many bytes were read


## Named pipes --> `FIFO`
- Create with `mkfifio()`
  - Use the FIFO with `open()`

# `FIFO()` Example

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
void main() {
int r, newfifo, fd;
char completeMessage[512], readBuffer[10];
char stringToWrite[20] = "CHILD: Hi parent!@@";
pid_t spawnpid;
char* FIFOfilename = "myNewFifo";
newfifo = mkfifo(FIFOfilename, 0644); // Create the FIFO
spawnpid = fork(); // Fork the child, which will write into the pipe
switch (spawnpid) {
  case 0: // Child
    fd = open(FIFOfilename, O_WRONLY); // Open the FIFO for writing
    if (fd == -1) { perror("CHILD: open()"); exit(1);
    }
    write(fd, stringToWrite, strlen(stringToWrite)); // Write the entire string into the pipe
  exit(0);
  break; // Terminate the child
default: // Parent
  fd = open(FIFOfilename, O_RDONLY); // Open the FIFO for reading
  if (fd == -1) { perror("PARENT: open()");
  exit(1);
  }
  memset(completeMessage, '\0', sizeof(completeMessage)); // Clear the buffer
  while (strstr(completeMessage, "@@") == NULL) { // As long as we haven't found the terminal...
  memset(readBuffer, '\0', sizeof(readBuffer)); // Clear the buffer
  r = read(fd, readBuffer, sizeof(readBuffer) - 1); // Get the next chunk
  strcat(completeMessage, readBuffer); // Add that chunk to what we hÂave so far
  printf("PARENT: Message received from child: \"%s\", total: \"%s\"\n", readBuffer, completeMessage);
  if (r == -1) {
    printf("PARENT: r == -1, exiting\n");
    break;
  } // Check for errors
  if (r == 0) { printf("PARENT: r == 0, exiting\n");
  break;
  }
}
int terminalLocation = strstr(completeMessage, "@@") - completeMessage; // Where is the terminal
  completeMessage[terminalLocation] = '\0'; // End the string early to wipe out the terminal
  printf("PARENT: Complete string: \"%s\"\n", completeMessage);
  remove(FIFOfilename); // Delete the FIFO
  break;
  }
}
```
