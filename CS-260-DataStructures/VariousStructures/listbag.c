#include "listbag.h"
#include <assert.h>
#include "type.h"
#include <stdlib.h>


/*Bag interface*/
/* Function to initialize bag:
 * 	Pre: b is not null
 * 		Post: list implementing the bag is initialized, size = 0
 * 		*/
void initBag(struct bag* b){
	assert( b != NULL);
	b->l = (struct list*)malloc(sizeof(struct list));/*Allocate for the list implementing the bag*/
	initList(b->l);/*Initialize list*/
}

/* Function to add an element to the bag:
 * 	Pre: b is not null
 * 		Post: val is added to the bag ie the list implementing the bag*/
void addToBag(struct bag* b, TYPE val){
	assert(b);
	addFrontList(b-> l , val);
}

/* Function to remove an element from the bag:
 * 	Pre: b is not null
 * 		Post: Element (if found) removed from bag/list
 * 		*/
void removeFromBag(struct bag* b, TYPE val){
	assert(b != NULL);
	struct DLink *holder = b -> l -> head -> next;
	
	if (bagContains(b,val) == 1){
		printf("IT WAS FOUND!!! \n");
		struct DLink *delthis = (struct DLink *)malloc(sizeof(struct DLink *));
		delthis = b -> l -> head;
		while (delthis -> next != NULL){
			if (delthis -> value == val){
				_removeLink(b->l, delthis);
			}
			delthis = delthis -> next;
		}
		free(delthis);
		b -> l -> head -> next = holder;
		return;
	}
	b -> l -> head -> next = holder;
	printf("Value not found \n\n");
}



/*Function to test if an element exists in the bag
 * 	Pre: b is not null
 * 	*/
int bagContains(struct bag* b, TYPE val){
	int counter = 0;
	struct DLink *holder = b -> l -> head -> next;
	while (b -> l -> head -> next != NULL){
		if (b -> l -> head -> next -> value == val){
			printf("Value was found in the list at link # %d!\n", counter);
			b -> l -> head -> next = holder;
			return 1;
		}
		else	{
			b -> l -> head -> next = b -> l -> head -> next -> next;
			counter++;
		}
	}
	b -> l -> head -> next = holder;
	printf("Data not found \n");
	return 0;
}

/*Function to test if the bag is empty
 * 	Pre: b is not null
 * 	*/

int isEmptyBag(struct bag* b)
	{return b -> l -> size == 0;}

void freeBag(struct bag *b)	{
    while (b -> l -> head -> next != b -> l -> tail)
		 removeFrontList(b -> l);
}


