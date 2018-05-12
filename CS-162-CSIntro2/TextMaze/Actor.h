/*********************************************************************
 ** Program Filename: Actor.h
 ** Author: Brandon Dring
 ** Date: 3/11/16
 ** Description: all pure virtual functions for player and swan alike
 ** Input: none
 ** Output: none 
 *********************************************************************/

#ifndef Actor_h
#define Actor_h


class actor {
private:
	
public:
	virtual void findstart(int, int, class game) = 0;
	virtual void getinput(char &) = 0; 
	virtual void move(int, int, class game, class player) = 0;
	virtual int give_x() = 0;
	virtual int give_y() = 0;
	virtual char giveprev() = 0;
	virtual int checkplayer(int &,int &, class game, int, int, int &, int &, class player ) =0;
};

#endif /* Actor_h */
