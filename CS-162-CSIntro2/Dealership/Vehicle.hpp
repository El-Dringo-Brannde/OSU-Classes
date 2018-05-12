/*********************************************************************
 ** Program Filename: Vehicle.hpp
 ** Author: Brandon Dring
 ** Date: 1/29/16
 ** Description: declarations for Vehicle.cpp
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <stdio.h>
#include <string>
#include <iostream> 

using namespace std;


class vehicle {
private:
	
public:
	vehicle();
	
	int setlot_num();
	double change_miles();
	double set_price();
	string set_make();
	string set_model();
	string set_color();
	string set_fuel();
	
	
};

#endif /* Vehicle_hpp */
