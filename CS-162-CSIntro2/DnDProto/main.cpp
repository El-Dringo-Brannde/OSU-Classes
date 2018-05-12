#include "Declarations.h"


int main(int argc, const char * argv[]) {
	int attack= 0, defend = 0, att_hold;
	srand(time(NULL)); //initialize time
	
	creature **monsters = new creature* [5]; //creates and fills array with
	monsters [0] = new gollum;	//different object types
	monsters [1] = new baba;
	monsters [2] = new blue_men;
	monsters [3] = new unicorn;
	monsters [4] = new barb;
	
	intro();
	
	do {
		fighter();
		choose_attack(monsters, attack);
		tofight();
		choose_defender(attack, defend, att_hold, monsters);
		
	} while (monsters[0] != NULL || monsters[1] != NULL || monsters[2] != NULL
					|| monsters[3] != NULL || monsters[4] != NULL);
		//to check if all the monsters are dead		
	delete [] monsters; 			
	return 0;

	}	



void choose_defender(int attack, int defend, int att_hold, creature **monsters){
	do {
	cin >> defend;
	if (monsters [defend - 1] == NULL)
		cout << "Character being attacked is dead! Try again!" << endl;
	}	while (monsters[defend - 1] == NULL);
	if (attack == 4 && defend == 4){
		cout << "Golly gosh the Unicorn is going nuts!" << endl;
		while (monsters[defend -1] != NULL){
			att_hold = monsters[attack - 1] -> attack();
			if (monsters[defend - 1] -> defense(att_hold) == 0){
			delete monsters [defend -1];
			monsters [defend - 1] = NULL;
}	
			cout << endl;
		}
		return;
	}
	att_hold = monsters[attack - 1] -> attack(); //holds attack value
	
	if (monsters[defend - 1] -> defense(att_hold) == 0){
		delete monsters[defend -1];
		monsters [defend - 1] = NULL; //checks to make sure isn't dead
	}
	cout << endl;
}





void choose_attack(creature **monsters, int &attack){
	do {
		cin >> attack;
		if (monsters[attack - 1] == NULL)
			cout << "That attacking character has died try again!" << endl;
	} while(monsters[attack - 1] == NULL);
	cout << endl;
}


void intro(){
	cout << " \t \t WELCOME!!!!" << endl << "Let's play what is near as makes no" << endl <<  "difference "
	<< "Dungeons and Dragons!!!" << endl;
	cout << "Let the games begin!!!" << endl << endl;
}


void fighter(){
	cout << "Pick who you want to fight." << endl;
	cout << "1.) Gollum (GOLLUM!!)" << endl;
	cout << "2.) Baba Yaga" << endl;
	cout << "3.) Blue men/Pixies" << endl;
	cout << "4.) Unicorn" << endl;
	cout << "5.) Barbarian" << endl;
}

void tofight(){
	cout << endl <<  "Now pick who to face off against!" << endl;
	cout << "1.) Gollum (GOLLUM!!)" << endl;
	cout << "2.) Baba Yaga" << endl;
	cout << "3.) Blue men/Pixies" << endl;
	cout << "4.) Unicorn" << endl;
	cout << "5.) Barbarian" << endl;
}
