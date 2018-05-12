/*********************************************************************
 ** Program Filename: Barbarian.cpp
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Attack, Defense & constructor of Barbarians
 ** Input: None
 ** Output:	Dependant on Rand rolls
 *********************************************************************/

#include "Barbarian.h"
#include "Declarations.h" 

barb::barb(){
	barb_armor = 0;
	barb_str = 12;
}

/*********************************************************************
 ** Function: barb :: defense
 ** Description: calculates the defense w/ armor
 ** Parameters: int damage_in
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int barb :: defense(int damage_in){	
	int barb_def = 0, temp = 0;
	for (int j = 0; j < 2; j++){
		 temp = rand() % 6;
		barb_def += temp;
	}
	cout << "Conan had " << barb_def << " points of defense, plus " << barb_armor
	<< " points of armor " << endl;
	barb_def += barb_armor;
	damage_in -= barb_def;
	if (damage_in < 0)
		damage_in = 0;
	
	cout << "The net damage taken by Conan is " << damage_in << " points!" << endl << endl;
	return change_hp(damage_in);
}

/*********************************************************************
 ** Function: barb :: attack
 ** Description: does the attack roll for barbarian (rand)
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int barb :: attack()	{
	int barb_dam = 0, temp= 0;
	for (int i = 0; i < 2; i++){
		temp = rand() % 6;
		barb_dam += temp;
	}
	cout << "Conan attack rolls " << barb_dam << endl;
	return barb_dam;
}

/*********************************************************************
 ** Function: barb :: change_hp
 ** Description: Changes the HP of creature, or declares dead
 ** Parameters: int damage_in
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int barb :: change_hp(int damage_in)	{
	barb_str -= damage_in;
	if (barb_str < 0 || barb_str == 0){
		cout << "Conan the Barbarian has been terminated" << endl;
		return 0;
	}
	else
		cout << "Conan the Barbarian has " << barb_str << " Hit points left" << endl;
	return 1; 
}

