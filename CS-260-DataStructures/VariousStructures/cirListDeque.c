#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cirListDeque.h"

/* internal functions interface */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);

/* ************************************************************************
 * 	Deque Functions
 * 	************************************************************************ */

/* Initialize deque.
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	q is not null
 * 			post:	q->Sentinel is allocated and q->size equals zero
 * 			*/
void initCirListDeque (struct cirListDeque *q)	{
	
	q -> Sentinel = (struct DLink *)malloc(sizeof(struct DLink));
	assert(q -> Sentinel != 0);
	
	q -> size = 0;
	q -> Sentinel -> next = q -> Sentinel;
	q -> Sentinel -> prev = q -> Sentinel;
	
}

/* Create a link for a value.
 *
 * 	param: 	val		the value to create a link for
 * 		pre:	none
 * 			post:	a link to store the value
 * 			*/
struct DLink * _createLink (TYPE val)	{
	
	struct DLink *ptr = (struct DLink *) malloc(sizeof(struct DLink));

	ptr -> value = val;
	
	return ptr;
}




/* Adds a link after another link
 *
 * 	param: 	q		pointer to the deque
 * 		param: 	lnk		pointer to the existing link in the deque
 * 			param: 	newLnk	pointer to the new link to add after the existing link
 * 				pre:	q is not null
 * 					pre: 	lnk and newLnk are not null
 * 						pre:	lnk is in the deque 
 * 							post:	the new link is added into the deque after the existing link
 * 							*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk)	{
	
	lnk -> next -> prev = newLnk;
	newLnk -> next = lnk -> next;
	newLnk -> prev = lnk;
	lnk -> next = newLnk;
	q -> size++;
}

/* Adds a link to the back of the deque
 *
 * 	param: 	q		pointer to the deque
 * 		param: 	val		value for the link to be added
 * 			pre:	q is not null
 * 				post:	a link storing val is added to the back of the deque
 * 				*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) {
	struct DLink *link = _createLink(val);
	
	_addLinkAfter(q, q -> Sentinel -> next, link);
}

/* Adds a link to the front of the deque
 *
 * 	param: 	q		pointer to the deque
 * 		param: 	val		value for the link to be added
 * 			pre:	q is not null
 * 				post:	a link storing val is added to the front of the deque
 * 				*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)	{
	struct DLink *ptr = _createLink(val);
	_addLinkAfter(q, q -> Sentinel, ptr);
}

/* Get the value of the front of the deque
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	q is not null and q is not empty
 * 			post:	none
 * 				ret: 	value of the front of the deque
 * 				*/

TYPE frontCirListDeque(struct cirListDeque *q)
	{return q -> Sentinel -> next -> value; }


/* Get the value of the back of the deque
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	q is not null and q is not empty
 * 			post:	none
 * 				ret: 	value of the back of the deque
 * 				*/
TYPE backCirListDeque(struct cirListDeque *q)	{
	
	struct DLink *last;
	last = q -> Sentinel;
	int sizehold = q -> size;
	while (sizehold != 0){
		last = last -> next;
		sizehold--;
	}
	return last -> value;
}


/* Remove a link from the deque
 *
 * 	param: 	q		pointer to the deque
 * 		param: 	lnk		pointer to the link to be removed
 * 			pre:	q is not null and q is not empty
 * 				pre:	lnk is in the deque 
 * 					post:	the link is removed from the deque
 * 					*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)	{
	
	lnk -> prev -> next = lnk -> next;
	lnk -> next -> prev = lnk -> prev;
	q -> size--;
	free(lnk);
}

/* Remove the front of the deque
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	q is not null and q is not empty
 * 			post:	the front is removed from the deque
 * 			*/
void removeFrontCirListDeque (struct cirListDeque *q){
		_removeLink(q, q -> Sentinel -> next);
}


/* Remove the back of the deque
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	q is not null and q is not empty
 * 			post:	the back is removed from the deque
 * 			*/
void removeBackCirListDeque(struct cirListDeque *q){
	struct DLink *last;
	last = q -> Sentinel;
	int sizehold = q -> size;
	while (sizehold != 0){
		last = last -> next;
		sizehold--;
	}
	_removeLink(q, last);
}

/* De-allocate all links of the deque
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	none
 * 			post:	All links (including backSentinel) are de-allocated
 * 			*/
void freeCirListDeque(struct cirListDeque *q)	{
	while (q -> size != 0)
		removeFrontCirListDeque(q);
	free (q -> Sentinel);
}

/* Check whether the deque is empty
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	q is not null
 * 			ret: 	1 if the deque is empty. Otherwise, 0.
 * 			*/
int isEmptyCirListDeque(struct cirListDeque *q)
	{return q -> size == 0;}
 


/* Print the links in the deque from front to back
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	q is not null and q is not empty
 * 			post: 	the links in the deque are printed from front to back
 * 			*/
void printCirListDeque(struct cirListDeque *q) {
	
	struct DLink *currptr;
	assert(!isEmptyCirListDeque(q));
	currptr = q -> Sentinel -> next;
	
	do {
		printf("Data: %d \n", currptr -> value);
		currptr = currptr -> next;
	}while(currptr != q -> Sentinel);
	
}

/* Reverse the deque
 *
 * 	param: 	q		pointer to the deque
 * 		pre:	q is not null and q is not empty
 * 			post: 	the deque is reversed
 * 			*/
void reverseCirListDeque(struct cirListDeque *q)	{
	struct DLink *currptr, *holder;
	currptr = q -> Sentinel -> next;
	holder = q -> Sentinel -> prev;
	struct DLink *temp;
	
	while (currptr != q -> Sentinel){
		currptr = currptr -> next;
		temp = currptr -> next;
	}
	
	printf("Data Reversal!!! \n \n");
	q -> Sentinel -> next = currptr -> prev;
	currptr = currptr -> prev;

	 while (currptr  != q -> Sentinel){
		 holder = currptr -> next;
		 currptr -> next = currptr -> prev;
		 currptr -> prev = holder;
		 currptr -> prev -> next =currptr;
		 currptr = currptr -> next;
	}
}









