
/*********************************************************************
 ** Program Filename: lost_list.cpp
 ** Author: Brandon Dring
 ** Date:	2/25/16
 ** Description:	prints lists, and pushes pointers on the stack, deletes stuff
 ** Input: none
 ** Output: none
 *********************************************************************/

#include "lose_list.h"

/*********************************************************************
 ** Function: fight_list()
 ** Description: constructor for fight_list
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
fight_list :: fight_list(){
	head = NULL;
	curr = NULL;
	temp = NULL;
}

/*********************************************************************
 ** Function: pushloser
 ** Description:	pushes the monster pointer onto stack
 ** Parameters: creature *player
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void fight_list :: pushloser(creature *player){
	node *n = new node;
	n -> next = NULL;
	n -> monst = player;
	
	if (head != NULL){
		curr = head;
		while (curr -> next != NULL)	//goes to last node of stack
			curr = curr -> next;
		curr -> next = n;
	}
	else
		head = n;
}


/*********************************************************************
 ** Function:	cleanup
 ** Description:	deletes all allocated memory
 ** Parameters:	num_monst
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void fight_list::cleanup(int num_monst) {
	node *delptr = NULL;
	creature *delmon = NULL;
	temp = head;
	curr = head;
	
	while (curr -> next != NULL) {
		temp = curr;
		curr = curr->next;	//goes to last node of stack
		
	}
	
	delptr = curr;
	delmon = curr -> monst;
	curr = curr->next;	// IMPORTANT STUFF
	temp->next = curr; //this adjusts the pointers accordingly
	
	delete delmon;
	delete delptr;
}

/*********************************************************************
 ** Function:	printlist
 ** Description:	prints all the monsters on the stack
 ** Parameters: num_monst
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void fight_list ::  printlist(int num_monst){
	num_monst = num_monst *2;
	curr = head;
	
	while (curr != NULL){
		cout << num_monst << ".)" << "[Team]:" << curr -> monst -> yell_team() <<
		"  " << curr -> monst -> yell_name() << endl << endl;
		curr = curr -> next;
		num_monst--;
	}
}


/*********************************************************************
 ** Function: printwinners
 ** Description:	prints the last 3 things pushed onto the stack
 ** Parameters:	num_monst
 ** Pre-Conditions:	none
 ** Post-Conditions:	none 
 *********************************************************************/
void fight_list :: printwinners(int num_monst) {
	int place = 3;
	int temp;
	temp = num_monst * 2 - place; //makes sure it prints only the last 3
	
	if (temp == -1)	//acounts for 1 v 1 battles
		place = 2;
	curr = head;
	for (int i = 0; i < temp; i++)	//adjusts to only 3 nodes left
		curr = curr -> next;
	
	while (curr != NULL && place > 0){
		cout << place << ".)" << "[Team]:" << curr -> monst -> yell_team() <<
		"  " << curr -> monst -> yell_name() << endl << endl;
		curr = curr -> next;
		place--;
	}
}
