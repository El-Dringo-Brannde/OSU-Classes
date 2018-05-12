
/*********************************************************************
 ** Program Filename: Fight_que.h
 ** Author: Brandon Dring
 ** Date: 2/25/16
 ** Description:	declarations for Fight_que
 ** Input:	None
 ** Output: None
 *********************************************************************/
#ifndef Fight_que_h
#define Fight_que_h

#include "main.h" 
#include <string>
#include "Creature.h"

class fight_que {
protected:
	struct que {
		creature *monst;
		que *next;
		que *prev;
		string teamname;
	};
	que *curr;
	que *tail;
public:
	que *head;
	fight_que();
	void push_fighter(creature *, int);
	creature *pop_fighter();
	void printfifo();
	
};

#endif /* Fight_que_h */
