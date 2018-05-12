#include "listbag.h"
#include "type.h"
#include <assert.h>
#include <stdlib.h>

/*
 * 	function to initialize the list, set the sentinels and set the size
 * 		param l the list
 * 			pre: l is not null
 * 				post: l size is 0
 * 				*/

void initList (struct list *l) {
	assert(l != NULL);
	l -> head = (struct DLink *) malloc(sizeof(struct DLink));
	l -> tail = (struct DLink *) malloc(sizeof(struct DLink));
	
	l -> head -> prev = NULL;
	l -> tail -> next = NULL;
	l -> head -> next = l -> tail;
	l -> tail -> prev = l -> head;
	l -> size = 0;
}


/*
 * 	_addLink
 * 		Funtion to add a value v to the list before the link l
 * 			param: l the list
 * 				param: lnk the  link to add before
 * 					param: v the value to add
 * 						pre: l is not null
 * 							pre: lnk is not null
 * 								post: l is not empty
 * 								*/

void _addLink(struct list *l, struct DLink *lnk, TYPE v)	{
	assert(l != NULL);
	assert(lnk != NULL);
	struct DLink *new = (struct DLink*) malloc (sizeof(struct DLink));
	
	new -> value = v;
	
	if (l -> size == 0){
		new -> next = l -> tail;
		new -> prev = l -> head;
		l -> head -> next = new;
		l -> tail -> prev = new;
		l -> size++;
	}
	
	if (lnk -> prev == l-> head ){
		new -> prev = l -> head;
		new -> next = l -> head -> next;
	
		lnk -> prev = new;
		l -> head -> next = new;
		l -> size++;
		return;
	}
	
	if (lnk -> next == l -> tail){
		new -> next = l -> tail;
		new -> prev = l -> tail -> prev;
		lnk -> next = new;
		l -> tail -> prev = new;
		l -> size++;
	}
}


/*
 * 	addFrontList
 * 		Function to add a value to the front of the list, can use _addLink()
 * 			param: l the list
 * 				param: e the element to be added
 * 					pre: l is not null
 * 						post: l is not empty, increased size by 1
 * 						*/

void addFrontList(struct list *l, TYPE e)	{
	_addLink(l,l -> head -> next,e);
}

/*
 * 	addBackList
 * 		Function to add a value to the back of the list, can use _addlink()
 * 			param: l the list
 * 				pre: l is not null
 * 					post: l is not empty
 * 					*/

void addBackList(struct list *l, TYPE e) {
	_addLink(l, l -> tail -> prev, e);
}

/*
 * 	frontList
 * 		function to return the element in the front of the  list
 * 			param: l the list
 * 				pre: l is not null
 * 					pre: l is not empty
 * 						post: none
 * 						*/

TYPE frontList (struct list *l) {
	return l -> head -> next -> value;
}

/*
 * 	backList
 * 		function to return the element in the back of the  list
 * 			param: l the list
 * 				pre: l is not null
 * 					pre: l is not empty
 * 						post: l is not empty
 * 						*/

TYPE backList(struct list *l)	{
	return l -> tail -> prev -> value;
}

/*
 * 	_removeLink
 * 		Function to remove a given link
 * 			param: l the list
 * 				param: lnk the linke to be removed
 * 					pre: l is not null
 * 						pre: lnk is not null
 * 							post: l size is reduced by 1
 * 							*/

void _removeLink(struct list *l, struct DLink *lnk)	{
	assert(l != NULL);
	assert(lnk != NULL);
	
	if (lnk -> prev == l -> head){
		l -> head -> next = lnk -> next;
		l -> head -> next -> prev = l -> head;
		free(lnk);
		l -> size--;
		return;
	}
	if (lnk -> next == l -> tail){
		l -> tail -> prev = lnk -> prev;
		l -> tail -> prev -> next = l -> tail;
		free (lnk);
		l -> size--;
	}
	else {
		lnk -> prev -> next = lnk -> next;
		lnk -> next -> prev = lnk -> prev;
		l -> size--;
		free(lnk);
	}
}

/*
 * 	removeFrontList
 * 		Function to remove element from front of list, can use _removelink()
 * 			param: l the list
 * 				pre:l is not null
 * 					pre: l is not empty
 * 						post: size is reduced by 1
 * 						*/

void removeFrontList(struct list *l)
	{	_removeLink(l, l -> head -> next);	}

/*
 * 	removeBackList
 * 		Function to remove element from back of list, can use _removelink()
 * 			param: l the list
 * 				pre: l is not null
 * 					pre:l is not empty
 * 						post: size reduced by 1
 * 						*/

void removeBackList(struct list *l)
	{	_removeLink(l, l -> tail -> prev);	}

/*
 * 	isEmptyList
 * 		param: q the list
 * 			pre: q is not null
 * 				post: none
 * 				*/

int isEmptyList(struct list *l) {
	assert(l != NULL);
	if (l -> head -> next != l -> tail)
		return 0;
	else
		return 1; 
}



/* Recursive implementation of contains()
 *  Pre: current is not null
 *   Post: 1 if found, 0 otherwise
 *    */
int _contains_recursive(struct DLink* current, TYPE e){
	if (current == NULL)
		return 0;
	if (current -> value == e)
		return 1;
	else
		return (_contains_recursive(current -> next, e));
}

/* Wrapper function for contains
 *  Pre: l is not null
 *   Post: 1 if found, 0 otherwise
 *    */
int listContains (struct list *l, TYPE e) {
	assert(!isEmptyList(l));
	return _contains_recursive(l->head, e);
}

/* Recursive implementation of remove()*/
void _remove_recursive(struct list *l, struct DLink* current, TYPE e, int* sz){
	assert( current != NULL);
	
	if (current -> value == e){
		printf("FOUND DATA! \n");
		_removeLink(l, current);
		return;
	}
	if (current == NULL)
		return;
	else
		return (_remove_recursive(l, current -> next, e, sz));
}






/* Wrapper for remove()*/
void listRemove (struct list *l, TYPE e) {
	assert (l != NULL);
	freeList(l);
}


void freeList(struct list *q)	{
	free(q -> head);
	free(q -> tail);
	free(q);
}




