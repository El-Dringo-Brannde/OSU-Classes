//
//  main.cpp
//  ChatClient
//
//  Created by Dring, Brandon on 2/8/18.
//  Copyright © 2018 Dring, Brandon. All rights reserved.
//

#include <iostream>
#include "CLI.hpp"
#include "chat.hpp"

using namespace std;


int main(int argc, char * argv[]) {
    cli CLA(argc, argv);
    
    cout << endl << "Hello " << CLA.Handle << " let's try to connect to " <<
        CLA.Hostname << ":" << CLA.PortNumber << endl << endl;
    
    chat ChatClient(CLA);
    
    return 0;
}
