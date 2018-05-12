//
//  Header.h
//  FTPServer
//
//  Created by Dring, Brandon on 3/10/18.
//  Copyright © 2018 Dring, Brandon. All rights reserved.
//

#ifndef Header_h
#define Header_h

// ------------ PROTOTYPES --------------
void pull_cli_args(int);
int address_init(char *);
struct addrinfo *create_address(char *);
int create_socket(struct addrinfo*);
int connect_socket(int, struct addrinfo*);
void bind_socket(int, struct addrinfo*);
void listen_to_socket(int);
void await_connections(int);
void accept_connections(int);
int parse_command_option(char *);

void send_back_file(int, char *);
void send_back_directory(int);
FILE * check_exists(char *, int);
#endif /* Header_h */
