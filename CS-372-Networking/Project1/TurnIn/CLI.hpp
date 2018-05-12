//
//  CLI.hpp
//  ChatClient
//
//  Created by Dring, Brandon on 2/8/18.
//  Copyright © 2018 Dring, Brandon. All rights reserved.
//

#ifndef CLI_hpp
#define CLI_hpp

#include <stdio.h>
#include <string>
using namespace std;


class cli {
public:
    cli(int, char **);
    
    string PortNumber;
    string Hostname;
    string Handle;
    string GetHandle();
};

#endif /* CLI_hpp */
