#include "chat.hpp"
#include "CLI.hpp"

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <cstdlib>


using namespace std;

// thanks Beej!

chat :: chat(cli CLA) {
    Handle = CLA.Handle;
    Port_Number = CLA.PortNumber;
    Host_Name = CLA.Hostname;
    
    Start();
}


void chat :: Create_Address() {
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints); // clear out struct
    
    hints.ai_family = AF_UNSPEC; // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream
    
    if (getaddrinfo(Host_Name.c_str(), Port_Number.c_str(), &hints, &res) != 0) {
        cout << "getaddrinfo error";
        exit(1);
    }
}


void chat :: Connect_To_Remote(){
    struct addrinfo * cur;
    
    for (cur = res; cur != NULL; cur = cur -> ai_next){
        Create_Socket(cur);
        if (Connect_Socket(cur) != -1){
            cout << "Connected!" << endl;
            break;
        }
    } // Since we're connecting with either HTTPS, HTTP, IPv4, or IPv6 loop through the possibilities
    if( cur == NULL) {
        cout << "Failed to Connect to remote host." << endl;
        exit(5);
    }
    Handle_Connection();
}


void chat :: Handle_Connection(){
    char Recv_Message[500], Outgoing_Message[500];
    long Send_Result, Recv_Result;
    string foo;
    
    int idx = 0;
    while(1) {
        cout << Handle << ">";
        if(idx == 0) // HACK: Since C strings suck ALOT
            cin.ignore();
        else
            cin.ignore(0); // prevents chopping off first character
        
        cin.getline(Outgoing_Message, sizeof(Outgoing_Message));

        Check_Quit(Outgoing_Message);
        
        Send_Result = send(Socket_FD, Outgoing_Message, strlen(Outgoing_Message), 0);
        if(Send_Result == -1) {
            cout << "Oh nose, did not send the message properly.. Self Destructing" << endl;
            exit(666);
        }

        Recv_Result = recv(Socket_FD, Recv_Message, 499, 0);
        if (Recv_Result == -1 || Recv_Result == 0){
            cout << "Error receiving message, self destructing." << endl;
            exit(666);
        }
        Check_Quit(Recv_Message);
        cout << Recv_Message << endl;
        
        memset(Recv_Message, 0, sizeof(Recv_Message));
        memset(Outgoing_Message, 0, sizeof(Outgoing_Message)); // clear out buffers
        idx++;
    }
}


void chat :: Check_Quit(string Outgoing_Message){
    if (Outgoing_Message == "\\quit"){
        cout << "I see you are trying to quit, goodbye" << endl;
        exit(0);
    }
}


void chat :: Create_Socket(struct addrinfo *cur) {
    Socket_FD = socket(cur->ai_family, cur -> ai_socktype, cur -> ai_protocol);
    if (Socket_FD == -1)
        cout << "Socket error: " << Socket_FD << endl;
}


int  chat :: Connect_Socket(struct addrinfo *cur) {
    Sock_Success = connect(Socket_FD, cur -> ai_addr, cur -> ai_addrlen);
    
    if (Sock_Success == -1)
        cout << "Error Connecting, trying again (Maybe)" << endl;
    return Sock_Success;
}

