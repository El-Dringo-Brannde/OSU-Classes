/*********************************************************************
 ** Program Filename: Blue_Men.cpp
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Does the attack, damage & constructor for blue men
 ** Input: none
 ** Output: depends on rand rolls
 *********************************************************************/

#include "Blue_men.h"
#include "main.h"


blue_men::blue_men(int var){
	if (var == 1)
		team = 1;
	else if (var == 2)
		team = 2; 
	cout << "SMURFS!" << endl;
	men_armor = 3;
	men_str = 12;
	dead = 1;
	men_max = 12; 
}

/*********************************************************************
 ** Function: yell_name()
 ** Description: tells program what monst it is
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string blue_men :: yell_name(){
	string temp;
	temp = "SMURFS!";
	return temp; 
}

/*********************************************************************
 ** Function: yell_team
 ** Description: tells what team they are on
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int blue_men :: yell_team(){
	return team; 
}

/*********************************************************************
 ** Function: isdead()
 ** Description: tells if they are dead or not
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: nones
 *********************************************************************/
int blue_men :: isdead(){
	return dead;
}

/*********************************************************************
 ** Function: heal()
 ** Description: brings smurfs back to full health
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
void blue_men :: heal(){
 cout << "Smurfs healed!" << endl;
	men_str = men_max; }


/*********************************************************************
 ** Function: blue_men :: attack
 ** Description: rolls the attack function of the Smurfs
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int blue_men :: attack(){
	int men_dam = 0, temp = 0;
	for (int i = 0; i < 2; i++){
		temp = rand() % 10;
		men_dam += temp;
	}
	cout << "The Smurfs have rolled " << men_dam << " points of attack" << endl
	<<  endl;
	return men_dam;
}

/*********************************************************************
 ** Function: blue_men :: defense
 ** Description: calculates the defense taken, w/ special ability
 ** Parameters: int damage_taken
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int blue_men :: defense(int damage_taken){
	int blue_def= 0, adj_array = (men_str/4), temp = 0; //adjusts die based on HP
	for (int j = 0; j < adj_array; j++) {
		temp =  rand() % 6;
		blue_def += temp;
	}
	cout << "The Smurfs rolled " << blue_def << " for defense, plus "
	<< endl <<  men_armor << " points worth of armor" << endl << endl;
	blue_def += men_armor;
	damage_taken -= blue_def;
	if (damage_taken < 0)
		damage_taken = 0;
	cout << "The Smurfs have taken a net " << damage_taken << " points!" << endl << endl;
	return change_hp(damage_taken);
}

/*********************************************************************
 ** Function: blue_men :: change_hp
 ** Description: changes the HP of the Smurfs or declares them dead
 ** Parameters: int damage_taken
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
int blue_men :: change_hp(int damage_taken)	{
	men_str -= damage_taken;
	if (men_str < 0 || men_str == 0) {
		cout << "All of the Smurfs are dead!" << endl;
		dead = 0; 
		return 0;
	}
	else
		cout << "The Smurfs have " << men_str << " Hit points left!" << endl;
	return 1; 
}