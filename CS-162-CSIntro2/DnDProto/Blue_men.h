/*********************************************************************
 ** Program Filename: Blue_men.h
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: declarations for Blue_men.cpp
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef Blue_men_h
#define Blue_men_h
#include "Creature.h" 

class blue_men : public creature{
private:
	int men_armor;
	int men_str; 
	
public:
	blue_men();
	int attack();
	int defense(int);
	int change_hp(int);
};

#endif /* Blue_men_h */
