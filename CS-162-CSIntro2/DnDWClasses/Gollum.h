/*********************************************************************
 ** Program Filename: Gollum.h
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Header files for Gollum.cpp
 ** Input: none
 ** Output: none
 *********************************************************************/

#ifndef Gollum_h
#define Gollum_h
#include "Creature.h"

class gollum: public creature{
private:
	int goll_armor;
	int goll_str;
	int team;
	int dead;
	int gollmax; 
public:
	gollum(int);
	int attack();
	int defense(int);
	int change_hp(int);
	string yell_name();
	int yell_team();
	void heal();
	int isdead();
};


#endif /* Gollum_h */
