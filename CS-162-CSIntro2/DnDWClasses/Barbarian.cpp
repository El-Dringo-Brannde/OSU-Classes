/*********************************************************************
 ** Program Filename: Barbarian.cpp
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Attack, Defense & constructor of Barbarians
 ** Input: None
 ** Output:	Dependant on Rand rolls
 *********************************************************************/

#include "Barbarian.h"
#include "main.h" 

barb::barb(int var){
	if (var == 1)
		team = 1;
	else if (var == 2)
		team = 2; 
	
	barb_armor = 0;
	barb_str = 12;
	dead = 1;
	barbmax = 12;
}

/*********************************************************************
 ** Function: yell_name()
 ** Description: tells program what monst they are
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string barb :: yell_name(){
	string temp;
	temp = "CONAN THE BARBARIAN is here!";
	return temp;
}

/*********************************************************************
 ** Function: isdead()
 ** Description: tells program if they are dead
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int barb :: isdead(){
	return dead;
}

/*********************************************************************
 ** Function: yell_team()
 ** Description: tells program what team they are on
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int barb :: yell_team()
{return team;}

/*********************************************************************
 ** Function: heal()
 ** Description: brings barb back to full health
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
void barb :: heal(){
 cout << "Conan healed!" << endl;
	barb_str = barbmax;
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
		dead = 0; 
		return 0;
	}
	else
		cout << "Conan the Barbarian has " << barb_str << " Hit points left" << endl;
	return 1; 
}

