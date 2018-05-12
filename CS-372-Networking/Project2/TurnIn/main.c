/*
    Project 2 - CS 372
    Implementing a FTP-like program to either transfer a single .txt file at a time,
    or list current directory.
    Extra credit was also done to transfer ANY file requested.

    By Brandon Dring
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <dirent.h>

#include "Header.h"

#define BUFFER_SIZE 500

/*
    ALOT of the code on setting up the socket and everything was taken from my
    first assignment we had done. Which in turn I referenced from Beej's guide,
    please refer to my first assignment for detailed references
*/


int main(int argc,  char * argv[]) {
    pull_cli_args(argc);

    int socket_fd = address_init(argv[1]);
    await_connections(socket_fd);

    return 0;
}

//Do the address initialize stuff here.
int address_init(char * port_number){
    struct addrinfo *res = create_address(port_number);
    int socket_fd = create_socket(res);
    bind_socket(socket_fd, res);
    listen_to_socket(socket_fd);
    return socket_fd;
}

// determine if CLA were valid
void pull_cli_args(int argc){
    if (argc != 2){
        printf("You need to specify what port to run on.. >.> \n");
        exit(1);
    }
}


// Actually make the socket
int create_socket(struct addrinfo *addr){
    int sock_fd = 0;
    if ((sock_fd = socket(addr ->ai_family, addr ->ai_socktype, addr->ai_protocol)) == -1){
        printf("Error creating the socket \n");
        exit(1);
    }
    return sock_fd;
}

// Fill out all the struct stuff.
struct addrinfo * create_address(char * port_number) {
    struct addrinfo hints;
    struct addrinfo *result;

    printf("Starting server on Port: %s... \n", port_number);

    memset(&hints, 0,  sizeof hints); // clear out the struct
    hints.ai_family = AF_INET; // using IPv4 addressing
    hints.ai_socktype = SOCK_STREAM; // using TCP Stream

    if(getaddrinfo(NULL, port_number, &hints, &result) != 0){
        printf("Hull breach!, error connecting to the port \n");
        exit(2);
    } else {
        return result;
    }
}

// Connect to my socket
int connect_socket(int sock_fd, struct addrinfo * addr){
    int socket_success = connect(sock_fd, addr -> ai_addr, addr -> ai_addrlen);
    if (socket_success == -1){
        printf("Could not connect to socket \n");
        exit(3);
    }
    return socket_success;
}

// Now we must bind to it
void bind_socket(int socket_fd, struct addrinfo* addr){
    if(bind(socket_fd, addr -> ai_addr, addr -> ai_addrlen) == -1){
        printf("Hull Breach! Could not bind to the port! \n");
        exit(4);
    }
}

// Now we are listening to it for connections
void listen_to_socket(int sock_fd){
    if (listen(sock_fd, 5) == -1){
        printf("Could not listen on the socket \n");
        exit(5);
    }
}

// Everything has been initialized, now wait.
void await_connections(int sock_fd){
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int new_fd;

    while (1){
        addr_size = sizeof(their_addr);
        new_fd = accept(sock_fd, (struct addrinfo *)&their_addr, &addr_size);
        printf("Connection Received \n");

        accept_connections(new_fd);
        close(new_fd);
        printf("Connection Terminated \n");
    }
}

// At this point we have been contacted, and now need to receive the data
void accept_connections(int file_descriptor){
    char command[100];
    char response_port[100];
    char name[100];
    char confirm[100] = "Received: ";
    printf("Receiving command.. \n");
    memset(command, 0, sizeof command);
    memset(response_port, 0, sizeof response_port);
    memset(name, 0, sizeof name);


    recv(file_descriptor, command, sizeof(command) -1, 0);
    strcat(confirm, command);
    send(file_descriptor, confirm, sizeof confirm, 0); //needed to clear out socket
    memset(confirm, 0, sizeof confirm);
    strcpy(confirm, "Received: ");

    if(strcmp(command, "-g") == 0){
        recv(file_descriptor, name, sizeof(name) -1, 0);
        strcat(confirm, name);
        send(file_descriptor, confirm, sizeof confirm, 0);
        memset(confirm, 0, sizeof confirm);
        strcpy(confirm, "Received: ");
    }else
        send(file_descriptor, "OK", sizeof "OK", 0);
    memset(confirm, 0, sizeof confirm);
    strcpy(confirm, "Received: ");



    recv(file_descriptor, response_port, sizeof(response_port) - 1, 0);
    strcat(confirm, response_port);
    send(file_descriptor, confirm, sizeof confirm, 0);

    if (parse_command_option(command) == 0)
        send_back_file(file_descriptor, name);
    else
        send_back_directory(file_descriptor);
} // WOW C strings suck.


// Determine what command they used (legality handled client side)
int parse_command_option(char * command){
    if (strcmp(command, "-g") == 0) // grab file
        return 0;
    if (strcmp(command, "-l") == 0) // grab directory
        return 1;
    else
        return -1;
}

// Send the file asked for
void send_back_file(int fd, char * name) {
    printf("Asked for file stream \n");
    sleep(2);
    FILE *file = check_exists(name, fd);
    char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));

    if(file == NULL)
        return; // we already sent back the error message, exit

    while (fgets(buf, sizeof(buf) - 1, file)){
        send(fd, buf, sizeof buf, 0);
        memset(buf, 0, sizeof(buf));
    }

    send(fd, "DONE", sizeof("DONE"), 0);
    fclose(file);
}

// We... Send back the directory asked
void send_back_directory(int fd) {
    printf("Asked for directory.. \n");
    sleep(1);
    DIR* directory = opendir(".");
    char file_name[5000];
    struct dirent * dp;
    memset(file_name, 0, sizeof file_name);

    while ((dp = readdir(directory)) != NULL){
        strcat(file_name, dp->d_name);
        strcat(file_name, " \n");
    }
    send(fd, file_name, sizeof (file_name), 0);
    send(fd, "DONE", sizeof "DONE", 0);
    sleep(1);
} // C strings strike again

// See if there is a file by such name
FILE * check_exists(char * name, int fd){
    FILE *file = fopen(name, "r");
    if(file == NULL)
        send(fd, "File Doesn't Exist", sizeof("File Doesn't Exist") - 1, 0);
    return file;
}
