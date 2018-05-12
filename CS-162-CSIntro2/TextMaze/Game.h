/*********************************************************************
 ** Program Filename: Game.h
 ** Author: Brandon Dring
 ** Date: 3/11/16
 ** Description: declarations and class for Game.cpp
 ** Input: none
 ** Output: none
 *********************************************************************/

#ifndef Game_h
#define Game_h
#include "Player.h"
using namespace std;

class game{
private:
	int width, height, num;
	char **maze, data;
	
public:

	bool testnorth(int, int, class player);
	bool testsouth(int, int, class player);
	bool testwest(int,int, class player);
	bool testeast(int, int, class player);
	
	bool playernorth(int,int);
	bool playersouth(int,int);
	bool playerwest(int,int);
	bool playereast(int,int);
	
	bool swantestsouth(int,int);
	bool swantestnorth(int,int);
	bool swantesteast(int,int);
	bool swantestwest(int,int);
	
	void print();
	void cleaner(int, int);
	void swancleaner(int,int);
	void openandget(int);
	int print(int, int, player &, int, int, int &);
	void update(int, int, char);
	void oldswansymb(int, int, char);
	void updateswanmap(int, int);
	void updateplaymap(int,int);
	
	int giveplaystart_X();
	int giveplaystart_Y();
	int giveswanstart_X();
	int giveswanstart_Y();
	
	char findsymbol(int, int);
};



#endif /* Game_h */
