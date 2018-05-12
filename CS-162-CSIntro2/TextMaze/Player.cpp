/*********************************************************************
 ** Program Filename: Player.cpp
 ** Author: Brandon Dring
 ** Date: 3/11/16
 ** Description: Contains all the getters and setters for the player object
	 or the move, sendplayer back functions that are needed
 ** Input: consists of WASD
 ** Output: updates map with new position
 *********************************************************************/
#include "main.h"
#include "Player.h"
#include "Game.h"
#include <string> 

player :: player(){
	keycount = 0;
	appcount = 0;
	starting_X = 0;
	starting_Y = 0;
	player_symbol = 'P';
	prev_symbol = 'z';
}


/*********************************************************************
 ** Function: checkplayer
 ** Description: does nothing, had to include it since I inherited from 
	 actor
 ** Parameters: x, y, maze mazegame, t ,d ,v ,q , player p1 junk values
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int player :: checkplayer (int &x, int &y, game mazegame, int t, int d, int &v, int &q, player p1){
	return 1; 
}


/*********************************************************************
 ** Function: change_symb
 ** Description: used if the player runs over an A or K to make sure 
	 those aren't printed back to map
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: change_symb()
{ prev_symbol = ' '; }

/*********************************************************************
 ** Function: giveapple
 ** Description: adds apply to inventory
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int player :: giveapple()
{ return appcount; }


/*********************************************************************
 ** Function: takeapple
 ** Description: negates an apple
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player ::takeapple()
{ appcount--;}



/*********************************************************************
 ** Function: move
 ** Description: lets the user move around the map
 ** Parameters: tempx, tempy, game (object) mazegame, player (object) p1
 ** Pre-Conditions: must be within board
 ** Post-Conditions: none
 *********************************************************************/
void player :: move(int x, int y ,game mazegame, player p1) {
	mazegame.update(starting_X,starting_Y,prev_symbol);	//adds presymbol
	
	char moving;
	getinput(moving);
	if (moving == 'w'){
		 if (mazegame.testnorth(starting_X, starting_Y, p1) == false){
			cout << "Can't do that homie!!!" << endl;
			 move(x,y,mazegame,p1);
			 change_symb();
		}
		else
			starting_Y--;
	}
	else if (moving == 'a'){
		if (mazegame.testwest(starting_X, starting_Y,p1) == false){
			cout << "You suck! Try again!" << endl;
			move(x,y,mazegame,p1);
			change_symb();
		}
		else
			starting_X--;
	}
	else if (moving == 's'){
		if (mazegame.testsouth(starting_X,starting_Y,p1) == false){
			cout << "Can't go further down!" << endl;
			move(x,y,mazegame,p1);
			change_symb();
		}
		else
			starting_Y++;
	}
	else if (moving == 'd'){
		if (mazegame.testeast(starting_X, starting_Y,p1) == false){
			cout << "Don't do that.. " << endl;
			move(x,y,mazegame,p1);
			change_symb();
		}
		else
			starting_X++;
	}
	prev_symbol = mazegame.findsymbol(starting_X, starting_Y); //gets symb of new tile
	if (prev_symbol != 'P')
		mazegame.updateplaymap(starting_X,starting_Y); //places p1 on new tile

}



/*********************************************************************
 ** Function: sendplayer back
 ** Description: sends player back to start if he has been tagged by the swan
 ** Parameters: tempx, tempy, game (object) mazegame
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: sendplayerback(int &tempx, int &tempy, game mazegame){
	cout << "You been had!" << endl;
	starting_X = mazegame.giveplaystart_X();
	starting_Y = mazegame.giveplaystart_Y();
	mazegame.update(tempx,tempy,' '); //changes position to blank
	tempx = starting_X;
	tempy = starting_Y;
	prev_symbol = 'E';
}



/*********************************************************************
 ** Function:givekeys
 ** Description: returns keycount
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: non e
 *********************************************************************/
int player :: givekeys()
{ return keycount;}

/*********************************************************************
 ** Function:minuskey
 ** Description: takes key
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: minuskey()
{keycount --;}


/*********************************************************************
 ** Function: addkey
 ** Description: adds a key to user inventory
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: addkey()
{keycount++;}

/*********************************************************************
 ** Function: addapple
 ** Description: add apple to inventory
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: addapple()
{ appcount += 15;}

/*********************************************************************
 ** Function: resetkey
 ** Description: changes keycount back to 0 when new level is loaded
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: resetkey()
{ keycount = 0;}

/*********************************************************************
 ** Function: resetapp
 ** Description: resets the amount of apples in inventory after new level
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: resetapp()
{ appcount = 0;}

/*********************************************************************
 ** Function:getinput
 ** Description: lets the user enter WASD to move
 ** Parameters: moving
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: getinput(char &moving){
	do {
		cout << "Please use WASD to determine where to move " << endl <<
		"Or 'Q' to quit" <<endl;
		cin >> moving;
		if (moving == 'Q')
			exit(0);
	}while(moving != 'w' && moving != 'a' &&
			 moving != 's' && moving != 'd');
}

/*********************************************************************
 ** Function: findstart
 ** Description: assigns the starting values back to the player
 ** Parameters: tempx, tempy, game mazegame
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void player :: findstart(int x, int y, game mazegame){
	prev_symbol = mazegame.findsymbol(x,y);
	starting_X = x;
	starting_Y = y;
}

/*********************************************************************
 ** Function: giveprev
 ** Description: gives the prev_symbol the player is holding
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
char player :: giveprev()
{ return prev_symbol;}

/*********************************************************************
 ** Function: give_x
 ** Description: returns the starting value of player
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
int player :: give_x()
{ return starting_X; }

/*********************************************************************
 ** Function: give_y
 ** Description: gives starting y value of player
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 *********************************************************************/
int player :: give_y()
{ return starting_Y; }




