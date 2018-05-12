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
	
public:
	gollum();
	int attack();
	int defense(int);
	int change_hp(int);
};

#endif /* Gollum_h */
