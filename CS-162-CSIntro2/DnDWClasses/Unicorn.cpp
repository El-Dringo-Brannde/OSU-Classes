/*********************************************************************
 ** Program Filename: Unicorn.cpp
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Does the attack, defense and constructor of Unicorns
 ** Input: none
 ** Output: depends on rand rolls
 *********************************************************************/

#include "Unicorn.h" 
#include "main.h"

unicorn::unicorn(int var){
	cout << "Big dumb horse!" << endl;
	if (var == 1)
		team = 1;
	else if (var == 2)
		team = 2; 
	uni_armor = 3;
	uni_str = 18;
	unimax = 18; 
	dead = 1;
}
/*********************************************************************
 ** Function: isdead()
 ** Description:	tells the program monst is dead
 ** Parameters: none
 ** Pre-Conditions: noen
 ** Post-Conditions: none
 *********************************************************************/
int unicorn :: isdead(){
	return dead;
}
/*********************************************************************
 ** Function: heal
 ** Description: returns health to max
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void unicorn :: heal(){
 cout << "Unicorn healed!" << endl;
	uni_str = unimax; }

/*********************************************************************
 ** Function: yell_name
 ** Description:	just tells what the monst is
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string unicorn :: yell_name(){
	string temp;
	temp = "Big dumb horse!";
	return temp;
}

/*********************************************************************
 ** Function: yell_name()
 ** Description: justs tells team name for printing list
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int unicorn :: yell_team()
{return team; }

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
		dead = 0;
		return 0;
	}
	else
		cout << "The stupid horse has " << uni_str << " Hit points left" << endl;
	return 1;
}








