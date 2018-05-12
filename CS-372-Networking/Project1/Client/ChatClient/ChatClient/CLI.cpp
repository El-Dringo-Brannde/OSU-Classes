//
//  CLI.cpp
//  ChatClient
//
//  Created by Dring, Brandon on 2/8/18.
//  Copyright © 2018 Dring, Brandon. All rights reserved.
//

#include "CLI.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


cli :: cli(int ArgCount, char * ArgValue[]) {
    if (ArgCount <= 2){
        cout << "Please provide a port number & Handle >.>" << endl;
        exit(5);
    }
    
    Hostname = ArgValue[1];
    PortNumber = ArgValue[2];
    GetHandle();
}

string cli :: GetHandle(){
    cout << "Enter a handle for yourself" << endl;
    cin >> Handle;
    return Handle;
}
