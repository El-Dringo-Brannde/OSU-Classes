# Network Servers


# Non-concurrent server connection
  - 192.168.1.1
    - reserved for LAN
  - A server socket listens on specific port(80)
  - Decides on routing based on Server IP/Port & Client IP/Port
  1. Create network socket with `Socket()`
  2. Bind socket to port with `bind()`
  3. Start listening for connections on port with `listen()`
  4. loop and accept connections with `accept()`
  5. read and write on new socket with `send()` & `recv()`

## Binding a socket to a port
- Multiple processes allow a single machine to listen to many sockets
- Multiple calls to `bind()` will fail as socket is already taken
- Even after the program has quit, the socket might be open for a minute longer

## Listening for connections
- The `accept()` function takes next connection off of the listen queue for a socket

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
void error(const char *msg) {
  perror(msg);
  exit(1);
} // Error function used for reporting issues
int main(int argc, char *argv[]) {
  int listenSocketFD, establishedConnectionFD, portNumber, charsRead;
  socklen_t sizeOfClientInfo;
  char buffer[256];
  struct sockaddr_in serverAddress, clientAddress;
  if (argc < 2) {
    fprintf(stderr,"USAGE: %s port\n", argv[0]);
    exit(1);
  } // Check usage & args
  // Set up the address struct for this process (the server)
    memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
  portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
  serverAddress.sin_family = AF_INET; // Create a network-capable socket
  serverAddress.sin_port = htons(portNumber); // Store the port number
  serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process
  // Set up the socket
  listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  // Create the socket
  if (listenSocketFD < 0)
    error("ERROR opening socket");

    // Enable the socket to begin listening
    if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
    error("ERROR on binding");
    listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections
  // Accept a connection, blocking if one is not available until one connects
  sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
  establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
   if (establishedConnectionFD < 0)
    error("ERROR on accept");
  // Get the message from the client and display it
  memset(buffer, '\0', 256); charsRead = recv(establishedConnectionFD, buffer, 255, 0); // Read the client's message from the socket
  if (charsRead < 0)
    error("ERROR reading from socket");
    printf("SERVER: I received this from the client: \"%s\"\n", buffer);
  // Send a Success message back to the client
  charsRead = send(establishedConnectionFD, "I am the server, and I got your message", 39, 0); // Send success back
  if (charsRead < 0)
    error("ERROR writing to socket");
    close(establishedConnectionFD); // Close the existing socket which is connected to the client
  close(listenSocketFD); // Close the listening socket
  return 0;
}
responses
$ ./server 51717 &
[1] 21094
$ ./client localhost 51717
CLIENT: Enter text to send to the server, and then hit enter: AWESOMESAUCE
SERVER: I received this from the client: "AWESOMESAUCE"
CLIENT: I received this from the server: "I am the server, and I got your message"
[1]+  Done                    ./server 51717
```
# Get Multiserver slide

## Iterative Servers
  - Only one client at a time
  - Easy to design, maintain, and implement
  - No I/O, Processing is quick, order matters
