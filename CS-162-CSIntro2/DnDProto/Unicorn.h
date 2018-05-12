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


class unicorn : public creature {
private:
	int uni_armor;
	int uni_str;
public:
	unicorn();
	int attack();
	int defense(int);
	int change_hp(int);
};

#endif /* Unicorn_h */
