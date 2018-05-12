/*********************************************************************
 ** Program Filename: Gollum.cpp
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Does the attack and defense of Gollum & constructor
 ** Input: none
 ** Output: dependant on rand rolls
 *********************************************************************/

#include "Gollum.h"
#include "Declarations.h"

gollum :: gollum(){
	goll_armor = 1;
	goll_str = 8;
}

/*********************************************************************
 ** Function: Gollum::attack
 ** Description: does the rand roll for Gollums sneak attack and general attack
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int gollum :: attack(){
	int goll_hit = 0, lucky = 0, temp = 0;
	
	lucky = rand() % 20;
	if (lucky == 5){	//gollum's sneak attack
		cout << "Gollum uses the ring to sneak up on the opponent!!" << endl;
		for (int i = 0; i < 3; i++){
			temp = rand() % 6;
			goll_hit += temp;
		}
		cout << "Gollum did " << goll_hit << " worth of damage" << endl << endl;
		return goll_hit; 
	}
	else
		goll_hit = rand () % 6; ;
	cout << "Gollum did " << goll_hit << " worth of damage" << endl <<  endl;
	return goll_hit;
}

/*********************************************************************
 ** Function: gollum :: defense
 ** Description: does the defensive rolls, and factors in armor
 ** Parameters: int damage_in
 ** Pre-Conditions: must be an int passed in
 ** Post-Conditions: none
 *********************************************************************/
int gollum :: defense(int damage_in){
	int goll_def= 0, temp = 0;
	for (int j = 0; j < 2; j++){
		temp = rand() % 6;
		goll_def += temp;
	}
	cout << endl << "Gollum's defense rolled " << goll_def << " plus "
	<< goll_armor << endl<< " for armor" << endl << endl;
	goll_def += goll_armor;
	damage_in -= goll_def;
	if (damage_in < 0)
		damage_in = 0; 
	cout << "Gollum has taken a net " << damage_in << " points of damage" << endl;
	
	return change_hp(damage_in);
}

/*********************************************************************
 ** Function: change_hp
 ** Description: Changes the HP of the character, or declares dead
 ** Parameters: damage_in
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int gollum:: change_hp(int damage_in){
	goll_str -= damage_in;
	if (goll_str < 0 || goll_str == 0){
		cout << "Gollum has taken a permanent nap!" << endl;
		return 0;
	}
	else
		cout << "Gollum has " << goll_str << " hit points left!" << endl << endl;
	return 1;
}





