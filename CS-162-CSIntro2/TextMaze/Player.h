/*********************************************************************
 ** Program Filename: Player.h
 ** Author: Brandon Dring
 ** Date: 3/11/16
 ** Description: declarations and classes for Player.cpp
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef Player_h
#define Player_h

#include "Actor.h" 
#include "main.h"

class player : public actor {
private:
	int keycount,appcount;
	int starting_X, starting_Y;
	char player_symbol, prev_symbol;
	
public:

	player();
	void getinput(char &);
	void move(int, int, class game, class player);
	void findstart(int, int, class game);
	
	void addapple();
	int giveapple();
	void takeapple();
	
	void addkey();
	void checkswans(int &, int &, class game);
	int checkplayer (int &, int &, class game, int, int, int &, int &, class player );
	void sendplayerback(int &, int &, class game);
	void minuskey();
	void change_symb();
	void resetkey();
	void resetapp();
	
	int give_x();
	int give_y();
	int givekeys();
	
	char giveprev();
};

#endif /* Player_h */
