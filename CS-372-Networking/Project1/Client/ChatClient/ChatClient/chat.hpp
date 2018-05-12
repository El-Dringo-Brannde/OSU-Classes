//
//  chat.hpp
//  ChatClient
//
//  Created by Dring, Brandon on 2/9/18.
//  Copyright © 2018 Dring, Brandon. All rights reserved.
//

#ifndef chat_hpp
#define chat_hpp

#include <stdio.h>
#include "CLI.hpp"

class chat {
public:
    chat(cli CLA);
    void Create_Address();
    void Create_Socket(struct addrinfo *);
    int Connect_Socket(struct addrinfo *);
    void Connect_To_Remote();
    void Handle_Connection();
    void Check_Quit(string);
    
    void Start(){
        Create_Address();
        Connect_To_Remote();
    }

private:
    string Host_Name;
    string Handle;
    string Port_Number;
    
    int Socket_FD;
    int Socket_Conn;
    int Sock_Success;
    
    struct addrinfo* res;
};
#endif /* chat_hpp */
