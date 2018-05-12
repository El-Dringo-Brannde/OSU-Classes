/*********************************************************************
 ** Program Filename: Barbarian.h
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Declarations for Barbarian.cpp
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef Barbarian_h
#define Barbarian_h

#include "Creature.h"

class barb: public creature{
private:
	int barb_armor;
	int barb_str;
	int team;
	int dead;
	int barbmax; 
public:
	barb(int);
	int attack();
	int defense(int );
	int change_hp(int);
	string yell_name();
	int yell_team();
	int isdead();
	void heal(); 
	
};

#endif /* Barbarian_h */