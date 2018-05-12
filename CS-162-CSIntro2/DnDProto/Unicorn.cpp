/*********************************************************************
 ** Program Filename: Unicorn.cpp
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Does the attack, defense and constructor of Unicorns
 ** Input: none
 ** Output: depends on rand rolls
 *********************************************************************/

#include "Unicorn.h" 
#include "Declarations.h"

unicorn::unicorn(){
	uni_armor = 3;
	uni_str = 18;
}

/*********************************************************************
 ** Function: unicorn :: attack
 ** Description: Rolls the attack function of the Unicorn
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int unicorn :: attack (){
	int uni_attack = 0, temp = 0;
	for (int i = 0; i < 2; i++){
		temp = rand() % 6;
		uni_attack += temp;
	}
	uni_attack += rand() % 20;
	cout << "The unicorns dual attack were " << uni_attack << " points worth!"
	<< endl << endl;
	return uni_attack;
}

/*********************************************************************
 ** Function: unicorn :: defense
 ** Description: calculates damage taken w/ armor
 ** Parameters: int damage_in
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int unicorn :: defense(int damage_in){
	int uni_defense = 0, temp = 0;
	for (int i = 0; i < 2; i++){
		temp= rand () % 6;
		uni_defense += temp; 
	}
	cout << "The unicorn rolled " << uni_defense << " points of defense, plus " << endl <<
	uni_armor << " points worth of armor" << endl;
	uni_defense += uni_armor;
	damage_in -= uni_defense;
	
	if (damage_in < 0)
		damage_in = 0;
	cout << "The Unicorn has taken a net damage of " << damage_in << " points!" << endl;
	
	return change_hp(damage_in);
}

/*********************************************************************
 ** Function: unicorn :: change_hp
 ** Description: changes the HP of the creature or declares dead
 ** Parameters: int damage_in
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
int unicorn :: change_hp(int damage_in)	{
	uni_str -= damage_in;
	if (uni_str < 0 || uni_str == 0){
		cout << "The Unicorn has died HORRIBLY!" << endl;
		return 0;
	}
	else
		cout << "The stupid horse has " << uni_str << " Hit points left" << endl;
	return 1;
}








