
/*********************************************************************
 ** Program Filename:	Fight_que.cpp
 ** Author:	Brandon Dring
 ** Date: 2/25/16
 ** Description:	Pushes fighters, and pops fighters to battle, and prints
 ** Input:	none
 ** Output:	none
 *********************************************************************/

#include "Fight_que.h"


/*********************************************************************
 ** Function:
 ** Description:
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
fight_que :: fight_que(){
	head = NULL;
	tail = NULL;
	curr = NULL;
}


/*********************************************************************
 ** Function:
 ** Description:
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void fight_que::push_fighter(creature * player, int var){
	que *temp = new que;
	que *n = NULL;
	temp -> next = NULL;
	temp -> monst = player;

	if (head == NULL){
		temp -> prev = NULL;
		head = temp;
	}
	
	else	{
		n = head;
		while (n -> next != NULL)	//pushes to last node
			n = n -> next; 
		n -> next = temp;
		temp -> prev = n;
	}
}



/*********************************************************************
 ** Function: pop_fighter
 ** Description:	returns the pointer to the monster off the top of the stack
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
creature  *fight_que :: pop_fighter(){
	que  *delptr = NULL;
	creature *tempmonst = NULL;
	
	if (head == NULL){
		delptr = head;
		tempmonst = delptr -> monst;
		head = head -> next;
		delete delptr;
	}
	else	{
		delptr = head;
		tempmonst = head -> monst;
		head = head -> next;
		delete delptr;
	}
		
	return tempmonst;
}


/*********************************************************************
 ** Function: printfifo()
 ** Description:	prints all characters in fight lineup
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void fight_que:: printfifo(){
	int place = 1;
	curr = head;
	
	while (curr != NULL){
		cout << place << ".)" << curr -> monst->yell_name() << endl;
		curr = curr -> next;
		place++;
	}
	cout << endl;
}