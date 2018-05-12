/*********************************************************************
 ** Program Filename: swan.h
 ** Author: Brandon Dring
 ** Date: 3/11/16
 ** Description: all the declarations for swan.cpp
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef swan_h
#define swan_h
#include "main.h"

class swan : public actor {
private:
	int swan_x, swan_y;
	char prior_symb;
public:
	swan();
	void move(int, int, class game, class player);
	void getinput(char &);
	void findstart(int, int, class game);
	int checkplayer(int &, int &, class game, int, int, int &, int &, class player);
	
	int give_x();
	int give_y();
	
	char giveprev();
};


#endif /* swan_h */
