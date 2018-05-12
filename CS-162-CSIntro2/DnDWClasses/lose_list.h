
/*********************************************************************
 ** Program Filename:lose_list.h
 ** Author:	Brandon Dring
 ** Date: 2/25/16
 ** Description:	Declarations for Lost_list
 ** Input: none
 ** Output: none
 *********************************************************************/
#ifndef Fight_list_h
#define Fight_list_h

#include "main.h"
class fight_list {
private:
	struct node {
		class creature *mon; 
		node* next;
		creature *monst; 
	};
	node *head;
	node *curr;
	node *temp;
public:
	fight_list();
	void pushloser(creature *);
	void cleanup(int);
	void printlist(int);
	void printwinners(int);
	
};

#endif /* Fight_list_h */
