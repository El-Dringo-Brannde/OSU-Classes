/*********************************************************************
 ** Program Filename: Creature.h
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: The abstract class that other classes pull from
 ** Input: None
 ** Output: None
 *********************************************************************/

#ifndef Creature_h
#define Creature_h

#include <string> 

using namespace std;
class creature {
protected:
	class creature **monsters;
	int health;
	int def_val;
	int team;
	int dead;
public:

	virtual int yell_team() = 0;
	virtual int attack() = 0;
	virtual int defense(int) = 0;
	virtual int change_hp(int) = 0;
	virtual string yell_name() = 0;
	virtual int isdead() = 0;
	virtual void heal() = 0;
};




#endif /* Creature_h */
