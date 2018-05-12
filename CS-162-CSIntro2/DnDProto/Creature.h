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


class creature {
protected:
	class creature **monsters;
public:
	virtual int attack() = 0;
	virtual int defense(int) = 0;
	virtual int change_hp(int) = 0;
};




#endif /* Creature_h */
