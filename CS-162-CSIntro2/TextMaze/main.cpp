/*********************************************************************
 ** Program Filename: Main.cpp
 ** Author: Brandon Dring
 ** Date: 3/11/16
 ** Description: Lets user navigate through a maze, with a swan chasing after 
	 them must get keys to get through doors, and apples to fend off swans
 ** Input: dependant on user
 ** Output: dependant on user
 *********************************************************************/

#include "main.h"
int main(int argc, const char * argv[]) {
	
	int level_count = 0;
	
	if (argc == 1){
		cout << "Please enter the number of levels to be used" << endl;
		exit(0);
	}
	level_count = atoi(argv[1]); //gets the level count
	if (level_count > 3){
		cout << "Please enter less than 3 levels, that's all I have built" << endl;
		exit(0);
	}

	srand(time(NULL));
	
	game mazegame;
	player p1;
	actor ** monst = new actor *[0];
	monst[0] = new swan;
	
	int playstart_x = 0, playstart_y = 0, swanstart_x = 0, swanstart_y = 0;
	int tempx = 0, tempy = 0,swanx = 0, swany = 0, level_arr = 0, turn = 0;
	string junk;
	
	cout << "I designed my own levels and tested the all rubric around them.. " << endl <<
	"test my features on your own levels at your own risk.." << endl <<
	"Please read the reflections first. " << endl;
	cout << endl << "Press anything to sign the waiver :) " <<endl;
	cin >> junk;
	
	intro(mazegame, level_arr);
	givebegining(playstart_x,playstart_y, swanstart_x, swanstart_y,mazegame); //get start positions
	monst [0] -> findstart(swanstart_x, swanstart_y, mazegame); //finds swan start
	p1.findstart(playstart_x,playstart_y, mazegame); //give player start
	
		while(level_arr != level_count){
			getplaycoord(tempx,tempy,p1, swanx, swany, monst); //update player position
		
			p1.move(tempx,tempy,mazegame,p1);
			monst[0] -> move(swanx,swany,mazegame, p1);
		
			getplaycoord(tempx,tempy,p1, swanx, swany, monst); //cleans the map of extra characters
			mazegame.swancleaner(swanx,swany);
			getplaycoord(tempx,tempy,p1, swanx, swany, monst);
			mazegame.cleaner(tempx,tempy);

			mazegame.print();
			if (mazegame.print(tempx,tempy,p1,swanx,swany,level_arr) == 5){ //checks to make sure player didn't get a ladder
				givebegining(playstart_x, playstart_y, swanstart_x, swanstart_y,mazegame);
				p1.findstart(playstart_x,playstart_y, mazegame);
				monst[0] -> findstart(swanstart_x, swanstart_y, mazegame);
				turn = 0;
				if (level_arr == level_count){
					cout << "That's all folks!" << endl;
					cout << "You beat the game!" <<endl; 
					exit(0);
				}
			}

			if (monst[0] -> checkplayer(swanx,swany,mazegame,swanstart_x,swanstart_y, tempx, tempy, p1) == 1)
				p1.findstart(playstart_x,playstart_y, mazegame); //sends player back if found by swan
		
			if (monst[0] -> checkplayer(swanx,swany,mazegame,swanstart_x,swanstart_y, tempx, tempy, p1) == 0){
				p1.takeapple();
				cout << "The player has " << p1.giveapple() << " risk free swan encounters left" << endl;
			}
			
			turn++;
			if (turn == 30){
				cout << "This is where I would spawn a new swan, but I couldn't figure that out :(" << endl <<
				"dock me if you must.. " << endl;
				turn = 0;
			}
	}
	return 0;
}


/*********************************************************************
 ** Function: givebegining
 ** Description: gives the swan(s) and player their starting positions
 ** Parameters: playstart_x, playstart_y, swanstart_x, swanstart_y, game mazegame
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
void givebegining(int &playstart_x, int &playstart_y, int &swanstart_x, int &swanstart_y, game &mazegame ){
	playstart_x = mazegame.giveplaystart_X();
	playstart_y = mazegame.giveplaystart_Y();
	swanstart_x = mazegame.giveswanstart_X();
	swanstart_y = mazegame.giveswanstart_Y();
}



/*********************************************************************
 ** Function:
 ** Description:
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void getplaycoord(int &playerx, int &playery, player &p1,  int &swanx, int &swany,  actor **monst){
	playerx = p1.give_x();
	playery = p1.give_y();
	swanx =  monst[0] -> give_x();
	swany = monst [0] -> give_y();
}

/*********************************************************************
 ** Function:
 ** Description:
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void intro(game &mazegame, int &level_arr){
	cout << "Welcome to a txt based maze game!!" << endl;
	cout << "Here is your first level to go through" << endl;
	mazegame.openandget(level_arr);
}
