/*********************************************************************
 ** Program Filename: Baba_Yaha.cpp
 ** Author: Brandon Dring
 ** Date: 2/12/16
 ** Description: Does the attack, defense and constructor for Baba_Yaga
 ** Input: none
 ** Output: dependant on dice roll
 *********************************************************************/

#include "Baba_Yaga.h"
#include "main.h"

baba::baba(int var){
	cout << "Baba Yaga!" << endl;
	if (var == 1)
		team = 1;
	else if (var == 2)
		team = 2; 
	baba_str = 12;
	baba_armor = 3;
	dead = 1;
	babamax = 12; 
}

/*********************************************************************
 ** Function: yell_name()
 ** Description: tells what monst they are
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
string  baba :: yell_name(){
	string temp;
	temp = "Baba Yaga!";
	return temp;
}

/*********************************************************************
 ** Function: heal()
 ** Description: returns baba to full health
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void baba :: heal(){
	cout << "Baba Yaga healed!" << endl;
	baba_str = babamax; }

/*********************************************************************
 ** Function: yell_team()
 ** Description: tells what team they are on
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int baba :: yell_team()
{return team; }

/*********************************************************************
 ** Function: isdead()
 ** Description: tells program if they are dead or not
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
int baba :: isdead()
{	return dead;}


/*********************************************************************
 ** Function: baba:: attack
 ** Description: does the attack roll and heals baba at the same time
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int baba::attack(){
	int baba_hit = 0;
	
	baba_hit += rand() % 6;
	
	cout << "Baba rolls " << baba_hit << " for attack!" << endl;
	baba_str += baba_hit;	//baba heal function
	cout << "Baba uses magic to heal herself for " << baba_hit << " points!!"
	<< endl << endl;
	return baba_hit;
}

/*********************************************************************
 ** Function: baba:: defense
 ** Description: calculates the damage taken w/ factoring in armor
 ** Parameters: int damage_taken
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int baba:: defense (int damage_taken){
	int baba_def= 0;
	baba_def = rand() % 10;
	cout << "Baba's defense rolled " << baba_def << " plus " << baba_armor << endl << 
	" points worth of armor!" << endl << endl;
	baba_def += baba_armor;
	damage_taken -= baba_def;
	if	(damage_taken < 0)
		damage_taken = 0;
	cout << "Baba had taken a net damage of " << damage_taken << " points!"
	<< endl << endl;
	
	return change_hp(damage_taken) ;
}

/*********************************************************************
 ** Function: Baba:: change_hp
 ** Description: changes the HP of creature, or declares them dead
 ** Parameters: int damage_taken
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int baba::change_hp(int damage_taken)	{	
	baba_str -= damage_taken;
	if (baba_str < 0 || baba_str == 0){
		cout << "Baba Yaga is sleeping with the fishes!!!" << endl << endl;
		dead = 0; 
		return 0;
	}
	else
		cout << "Baba Yaga has " << baba_str << " hit points left" << endl;
	return 1; 
}










