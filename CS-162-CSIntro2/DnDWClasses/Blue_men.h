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
#include <string>


class blue_men : public creature{
private:
	int men_armor;
	int men_str;
	int team;
	int dead;
	int men_max; 
public:
	blue_men(int);
	int attack();
	int defense(int);
	int change_hp(int);
	string  yell_name();
	int yell_team();
	int isdead();
	void heal(); 
};

#endif /* Blue_men_h */
