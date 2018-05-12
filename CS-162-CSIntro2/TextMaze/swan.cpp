/*********************************************************************
 ** Program Filename: swan.cpp
 ** Author: Brandon Dring
 ** Date: 3/11/16
 ** Description: all the getters and setters and player detection of the
	 swans. Along with the movement
 ** Input: dependant
 ** Output: dependant
 *********************************************************************/

#include "swan.h"
#include "main.h"

swan :: swan(){
	swan_x = 5;
	swan_y = 5;
	prior_symb = 't'; 
}


/*********************************************************************
 ** Function: move
 ** Description: generates a random input for the swan to move
 ** Parameters: swanx, swany, game (object) mazegame, player (object) p1
 ** Pre-Conditions: must be within board
 ** Post-Conditions: none
 *********************************************************************/
void swan :: move(int x, int y, game mazegame, player p1){
	
	char moving = 'w';
	getinput(moving);
	if (moving == 'w'){
		if (mazegame.swantestnorth(swan_x, swan_y) == true){
				//prior_symb = ' ';
			move(x,y,mazegame,p1);
		}
		else
			swan_y--;
	}
	else if (moving == 'a'){
		if (mazegame.swantestwest(swan_x, swan_y) == true){
				//			prior_symb = ' ';
			move(x,y,mazegame,p1);
		}
		else
			swan_x--;
	}
	else if (moving == 's'){
		if (mazegame.swantestsouth(swan_x,swan_y) == true){
				//prior_symb = ' ';
			move(x,y,mazegame,p1);
		}
		else
			swan_y++;
	}
	else if (moving == 'd'){
		if (mazegame.swantesteast(swan_x, swan_y) == true){
				//prior_symb = ' ';
			move(x,y,mazegame,p1);
		}
		else
			
			swan_x++;
	}
	prior_symb = mazegame.findsymbol(swan_x, swan_y); //gets symb of new tile
	mazegame.updateswanmap(swan_x,swan_y); //places swan on new tile
}
 


/*********************************************************************
 ** Function: checkplayer
 ** Description: checks to see if the player is in an adjacent tile,
	 then checks to see if they have any apples
 ** Parameters: swantempx, swantempy, game (object) mazegame, swanstart_x, 
	 swanstart_y, tempx, tempy, player(object) p1
 ** Pre-Conditions: must be within board
 ** Post-Conditions: none
 *********************************************************************/
int swan :: checkplayer (int &swantempx, int &swantempy, game mazegame, int swanstart_x, int swanstart_y, int &tempx, int &tempy, player p1)	{
	
	if (mazegame.playernorth(swantempx,swantempy) == true){
		if (p1.giveapple() != 0)
			return 0;
		else{
			cout << "The swan has found the player!" << endl;
			swan_x = swanstart_x;
			swan_y = swanstart_y;
			swantempx = swan_x;
			swantempy = swan_y;
			return 1;
		}
	}
	else if (mazegame.playereast(swantempx,swantempy) == true){
		if (p1.giveapple() != 0)
			return 0;
		else {
		cout << "The swan has found the player!" << endl;
		swan_x = swanstart_x;
		swan_y = swanstart_y;
		swantempx = swan_x;
		swantempy = swan_y;
		return 1;
		}
	}
	else if (mazegame.playersouth(swantempx,swantempy) == true){
		if (p1.giveapple() != 0)
			return 0;
		else {
		cout << "The swan has found the player!" << endl;
		swan_x = swanstart_x;
		swan_y = swanstart_y;
		swantempx = swan_x;
		swantempy = swan_y;
		return 1;
		}
	}
	else if (mazegame.playerwest(swantempx,swantempy) == true){
		if (p1.giveapple() != 0)
			return 0;
		else {
		cout << "The swan has found the player!" << endl;
		swan_x = swanstart_x;
		swan_y = swanstart_y;
		swantempx = swan_x;
		swantempy = swan_y;
		return 1;
		}
	}
	
	return 2;
}


/*********************************************************************
 ** Function: give_x
 ** Description: returns the x value of where the swan is
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int swan :: give_x()
{	return swan_x;}

/*********************************************************************
 ** Function: give_y
 ** Description: returns the y value of where the swan is
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int swan :: give_y()
{ return swan_y; }


/*********************************************************************
 ** Function: giveprev
 ** Description: returns the previous value held by where the swan was
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
char swan :: giveprev()
{ return prior_symb; } 


/*********************************************************************
 ** Function: findstart
 ** Description: gets the starting values for the swan
 ** Parameters: swanx, swany, game (object) mazegame
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void swan :: findstart(int x, int y, game mazegame){
	prior_symb = mazegame.findsymbol(x,y);
	swan_x = x;
	swan_y = y;
}


/*********************************************************************
 ** Function: getinput
 ** Description: generates a random number and translates it to a char for
	 movement
 ** Parameters: moving
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
void swan :: getinput (char &moving){
	int temp = 0;
		temp = rand() % 8;
	if (temp == 0 || temp == 4)
		moving ='w';
	else if (temp == 1 || temp == 5)
		moving = 'a';
	else if (temp == 2 || temp == 6)
		moving = 's';
	else if (temp == 3 || temp == 7)
		moving = 'd';
	
}