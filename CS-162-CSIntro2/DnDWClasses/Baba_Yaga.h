/*********************************************************************
 ** Program Filename: Baba_Yaga.h
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Header files for Baba_Yaga.cpp
 ** Input: None
 ** Output: none 
 *********************************************************************/

#ifndef Baba_Yaga_h
#define Baba_Yaga_h
#include "Creature.h"

class baba : public creature {
private:
	int baba_str;
	int baba_armor;
	int team;
	int babamax; 
public:
	baba(int);
	int attack();
	int defense(int);
	int change_hp(int);
	string yell_name();
	int yell_team();
	void heal();
	int isdead();
};
#endif /* Baba_Yaga_h */
