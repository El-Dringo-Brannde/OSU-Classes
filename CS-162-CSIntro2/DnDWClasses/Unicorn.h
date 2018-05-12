/*********************************************************************
 ** Program Filename: Unicorn.h
 ** Author: Brandon Dring
 ** Date: 2/16/12
 ** Description: Declarations for Unicorn.cpp
 ** Input: none
 ** Output: none
 *********************************************************************/

#ifndef Unicorn_h
#define Unicorn_h
#include "Creature.h" 
#include <string> 


class unicorn : public creature {
private:
	int uni_armor;
	int uni_str;
	int team;
	int dead;
	int unimax; 
public:
	unicorn(int);
	int attack();
	int defense(int);
	int change_hp(int);
	string yell_name();
	int yell_team();
	int isdead();
	void heal();
};

#endif /* Unicorn_h */
