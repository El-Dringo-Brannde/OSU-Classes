
/*********************************************************************
 ** Program Filename: main.cpp
 ** Author: Brandon Dring
 ** Date: 2/25/16
 ** Description: runs the whole DnD tourny
 ** Input: none
 ** Output: none
 *********************************************************************/

#include "main.h"


int main(int argc, const char * argv[]) {
	int num_monst, choice, fight_pick;
	int test_1, test_2;
	string cont;
	
	creature *play_1, *play_2;
	fight_que team_1, team_2;
	fight_list loser_stack;
	
	intro();
	cout << "How many monsters do you want each team to get?" << endl;
	cin >> num_monst;
	
	cout << "Team 1, you pick your fighters!" << endl;
	for (int i = 0; i < num_monst; i++)	{	//sets fighters for team 1
		creature *c;
		int var = 1;
		c = get_creature(fight_pick, choice, c, var);
		team_1.push_fighter(c, var);
	}

	cout << "Team 2, pick your fighters!" << endl;	//sets fighters for team 2
	for (int i = 0; i < num_monst; i++){
		creature *c;
		int var = 2;
		c = get_creature(fight_pick, choice, c, var);
		team_2.push_fighter(c, var);
	}

	while (team_1.head != NULL && team_2.head != NULL){
		cout << "Team 1 has.. " << endl;
		team_1.printfifo();
		cout << "Team 2 has.. " << endl;
		team_2.printfifo();

		cout << "Press any key to continue!" << endl; // allows stopage to see whats left of team
		cin.ignore();
		cin >> cont;
		
		play_1 = team_1.pop_fighter();	//gets fighters
		play_2 = team_2.pop_fighter();
	
	do {
		
		cout << endl << "Player 1 rolls.. " << endl << "-----------------------" <<endl;
		test_1 = play_1 -> attack();
		cout << "Player 2 rolls.. " << endl << "------------------------" <<  endl;
		test_2 = play_2 -> attack();
		cout << "The resulting attacks are.. " << endl << "------------------" << endl;
	}	while(play_1 -> defense(test_2) != 0 && play_2 -> defense(test_1) != 0);
	
		
		if (play_2 -> isdead() == 0){	//checks if dead, pushes to stack, and heals winner
			cout << "Player 2 died" << endl;
			loser_stack.pushloser(play_2);
			cout << "[Team]: " << play_1 -> yell_team() << " " << play_1 -> yell_name() << " Won that battle!" << endl;
			play_1 -> heal();
			team_1.push_fighter(play_1,1);
	}
		
		if (play_1 -> isdead() == 0){		//checks if dead, pushes to stack, and heals winner
			cout << "Player 1 died!" << endl;
			loser_stack.pushloser(play_1);
			cout <<  "[Team]: " << play_2 -> yell_team() << " " << play_2 -> yell_name() <<" Won that battle!" << endl;
			play_2 -> heal();
			team_2.push_fighter(play_2,1);
	}
		
		
		cout << endl << "LOSER PILE!!!" << endl << "--------------------" << endl;
		loser_stack.printlist(num_monst);
	
		cout << "Press anything to continue!!! " << endl;
		cin.ignore();
		cin >> cont;
	}
	
	
	if (team_1.head == NULL){	// pushes all remaining players on team 2 to loser stack
		cout << endl << "*************************************************" << endl <<
		"Team 2 has won the tournament!!! " << endl << "All hail Team 2!!!" << endl <<
		"*********************************************" << endl;
		while (team_2.head != NULL){
			play_2 = team_2.pop_fighter();
			loser_stack.pushloser(play_2);
		}
	}
	else if (team_2.head == NULL){	// pushes all remaining players on team 1 to loser stack
		cout << endl << "************************************************" <<
		"Team 1 has won the tournament!!!" << endl << "All hail team 1!" << endl <<
		"********************************************"<< endl;
		while (team_1.head != NULL){
			play_1 = team_1.pop_fighter();
			loser_stack.pushloser(play_1);
		}
	}
	
	cout << "Let's show the top 3 finishers!" << endl
	<< "*******************************" << endl;
	loser_stack.printwinners(num_monst);
	cout << "The ending stack of losers!" << endl <<
	"***********************************************" << endl;
	loser_stack.printlist(num_monst);
	
	
	for (int i = 0; i < num_monst * 2; i++)	//deletes everything
		loser_stack.cleanup(num_monst);
	
    return 0;
}


/*********************************************************************
 ** Function: *get_creature
 ** Description:	creates the new pointer to monster and returns it
 ** Parameters:	fight_pick, choice, c, var
 ** Pre-Conditions: none
 ** Post-Conditions:	pick must be within bounds
 *********************************************************************/
creature *get_creature(int fight_pick, int choice, creature *c, int var){
	fight_pick = choose_fighter(choice);
	if (fight_pick == 1)
		c = new gollum(var);
	else if (fight_pick == 2)
		c = new baba(var);
	else if (fight_pick == 3)
		c = new blue_men(var);
	else if (fight_pick == 4)
		c = new unicorn(var);
	else if (fight_pick == 5)
		c = new barb(var);
	return c;
}


/*********************************************************************
 ** Function: fighter
 ** Description: displays the fighter to be used
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int choose_fighter(int choice){
	cout << "Pick who you want to fight." << endl;
	cout << "1.) Gollum (GOLLUM!!)" << endl;
	cout << "2.) Baba Yaga" << endl;
	cout << "3.) Blue men/Pixies" << endl;
	cout << "4.) Unicorn" << endl;
	cout << "5.) Barbarian" << endl;
	cin >> choice;
	return choice;
}


/*********************************************************************
 ** Function:intro
 ** Description: just introduces user to game
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void intro(){
	cout << " \t \t WELCOME!!!!" << endl << "Let's play what is near as makes no" << endl <<  "difference "
	<< "Dungeons and Dragons!!!" << endl;
	cout << "Let the games begin!!!" << endl << endl;
}
