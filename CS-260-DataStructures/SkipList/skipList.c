#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skipList.h"
#include <time.h>


/* ************************************************************************
 *  Main Function
 *   ************************************************************************ */
/* Test function:
 *  param: no parameters
 *   pre:	no parameres
 *    post: prints out the contents of the skip list */

void test(){
	srand(time(NULL));
	
	struct skipList *list1 = (struct skipList *)malloc(sizeof(struct skipList));
	struct skipList *list2 = (struct skipList *) malloc (sizeof(struct skipList));
	
	initSkipList(list1);
	initSkipList(list2);
	
	int i;
	for (i = 0;i < 20;i++) {
		int random = rand() % 101;
		int random2 = rand() % 101;
		addSkipList(list1, random);
		addSkipList(list2,random2);
	}
	
	
	struct skipLink *topholder = list1->topSentinel;
	
	printf(" \n \n List 1: \n");
	printSkipList(list1);
	printf("List 2:\n");
	printSkipList(list2);
	list1 -> topSentinel = topholder;
	
	printf("Searching for 100.. \n");
	if (containsSkipList(list1,100) == 1)
		printf("FOUND IT!!! \n");
	else
		printf("Sorry not found :( \n");
	
	
	mergeSkipList(list1,list2);
	printf(" \n \n ");
	printSkipList(list1);
	struct skipLink * bottom = list1 -> topSentinel;
	
	while (bottom -> down != NULL){
		bottom = list1 -> topSentinel -> down;
		list1 -> topSentinel -> down = list1 -> topSentinel -> down -> down;
	}
	
	list1 -> topSentinel = topholder;
	
	while (bottom != NULL){
		removeSkipList(list1, bottom -> value);
		bottom = bottom -> next;
	}
	free (list1 -> topSentinel);
	free (list2 -> topSentinel);
	free (list1);
	free (list2);
}


/* ************************************************************************
 *  Internal Functions
 *   ************************************************************************ */

/* Coin toss function:
 *  param: 	no parameters
 *   pre:	no parameres
 *    post: output is a random intiger number in {0,1} */
int flipSkipLink(void)	{
	int temp = rand()%2;
	return temp;
}



/* Move to the right as long as the next element is smaller than the input value:
 *  param: 	current -- pointer to a place in the list from where we need to slide to the right
 *   param:	e --  input value
 *    pre:	current is not NULL
 *     post: returns one link before the link that contains the input value e */
struct skipLink * slideRightSkipList(struct skipLink *current, TYPE e){
	assert(current != NULL);
	
	while ((current->next != 0) && LT(current->next->value, e))
		current = current->next;
	return current;
}


/* Create a new skip link for a value
 * 	param: e	 -- the value to create a link for
 * 		param: nextLnk	 -- the new link's next should point to nextLnk
 * 			param: downLnk -- the new link's down should point to downLnk
 * 				pre:	none
 * 					post:	a link to store the value */
struct skipLink* newSkipLink(TYPE e, struct skipLink * nextLnk, struct skipLink* downLnk) {
	
	struct skipLink * tmp = (struct skipLink *) malloc(sizeof(struct skipLink));
	assert(tmp != 0);
	
	tmp->value = e;
	tmp->next = nextLnk;
	tmp->down = downLnk;
	
	return tmp;
}


/* Add a new skip link recursively
 *  param: current -- pointer to a place in the list where the new element should be inserted
 *   param: e	 -- the value to create a link for
 *    pre:	current is not NULL
 *     post: a link to store the value */
struct skipLink* skipLinkAdd(struct skipLink * current, TYPE e) {
	struct skipLink *newLink, *downLink;
	newLink = 0;
	assert(current != NULL);
	
	if (current->down == 0) {
		newLink = newSkipLink(e, current->next, 0);
		current->next = newLink;
	}
	else {
		downLink = skipLinkAdd(slideRightSkipList(current->down, e), e);
		if (downLink && flipSkipLink()) {
			newLink = newSkipLink(e, current->next, downLink);
			current->next = newLink;
		}
	}
	return newLink;
}


/* ************************************************************************
 *  Public Functions
 *   ************************************************************************ */

/* Initialize skip list:
 *  param:  slst -- pointer to the skip list
 *   pre:	slst is not null
 *    post: the sentinels are allocated, the pointers are set, and the list size equals zero */
void initSkipList (struct skipList *slst) {
	slst -> topSentinel = (struct skipLink *) malloc (sizeof(struct skipLink));
	assert (slst -> topSentinel != NULL);
	slst -> size = 0;
	
	slst -> topSentinel -> next = NULL;
	slst -> topSentinel -> down = NULL;
	
	
	
}

/* Checks if an element is in the skip list:
 *  param: slst -- pointer to the skip list
 *   param: e -- element to be checked
 *    pre:	slst is not null
 *     post: returns true or false  */
int containsSkipList(struct skipList *slst, TYPE e)	{
	assert(slst != NULL);
	
	struct skipLink *current = slst -> topSentinel;
	
	while (current != NULL){
		current = slideRightSkipList(current,e);
		
		if (current -> next != 0 && EQ(current -> next -> value , e))
			return 1;
		current = current -> down;
	}
	return 0;
}


/* Remove an element from the skip list:
 *  param: slst -- pointer to the skip list
 *   param: e -- element to be removed
 *    pre:	slst is not null
 *     post: the new element is removed from all internal sorted lists */
void removeSkipList(struct skipList *slst, TYPE e)	{
	assert (slst);
	struct skipLink *current, *temp;
	
	current = slst -> topSentinel;
	while (current) {
		current = slideRightSkipList(current,e);
		if (current -> next != 0 && EQ(current -> next -> value, e))	{
			temp = current -> next;
			current -> next = current -> next -> next;
			free (temp);
			if (current -> down == NULL)
				slst -> size--;
		}
		current = current -> down;
	}
}




/* Add a new element to the skip list:
 * 	param: slst -- pointer to the skip list
 * 		param: e -- element to be added
 * 			pre:	slst is not null
 * 				post:	the new element is added to the lowest list and randomly to higher-level lists */
void addSkipList(struct skipList *slst, TYPE e)	{
	assert(slst != NULL);
	
	struct skipLink *downlink, *newLink;
	downlink = skipLinkAdd(slideRightSkipList(slst->topSentinel,e),e);
	
	if (downlink != NULL && flipSkipLink() == 1){
		newLink = newSkipLink(e, NULL, downlink);
		slst -> topSentinel = newSkipLink(0,newLink, slst -> topSentinel);
	}
	slst -> size++;
	
}


/* Find the number of elements in the skip list:
 *  param: slst -- pointer to the skip list
 *   pre:	slst is not null
 *    post: the number of elements */
int sizeSkipList(struct skipList *slst)	{
	return slst -> size;
}

/* Print the links in the skip list:
 * 	param: slst -- pointer to the skip list
 * 		pre:	slst is not null and slst is not empty
 * 			post: the links in the skip list are printed breadth-first, top-down */
void printSkipList(struct skipList *slst)	{
	struct skipLink *topholder = slst->topSentinel;
	
	while (slst -> topSentinel != NULL)	{
		struct skipLink *nextholder = slst -> topSentinel -> next;
		
		while (slst -> topSentinel -> next != NULL){
			printf("%d  ", slst -> topSentinel -> next -> value);
			slst -> topSentinel -> next = slst -> topSentinel -> next -> next;
		}
		slst -> topSentinel -> next = nextholder;
		printf("\n");
		slst -> topSentinel  = slst -> topSentinel -> down;
	}
	slst -> topSentinel = topholder;
}

/* Merge two skip lists, by adding elements of skip list 2 to skip list 1
 *  that are not already contained in skip list 1.
 *   The function is also supposed to remove the entire skip list 2 from the memory.
 *    param: slst1 -- pointer to the skip list 1
 *     param: slst2 -- pointer to the skip list 2
 *      pre: slst1 and slst2 are not null, and skip list 1 and skip list 2 are not empty
 *       post: slst1 points to the merger skip list,  slst2 is null*/
void mergeSkipList(struct skipList *slst1, struct skipList *slst2)	{
	assert (slst1 && slst2 != NULL);
	struct skipLink *bottom  = slst2 -> topSentinel;
	struct skipLink *top = bottom;

	while (bottom -> down!= NULL){
		bottom = slst2 -> topSentinel -> down;
		slst2 -> topSentinel -> down = slst2 -> topSentinel -> down -> down;
	}
	
	slst2 -> topSentinel = top; 
	while (bottom -> next  != NULL){
			if (containsSkipList(slst1, bottom -> next -> value) == 0){
				addSkipList(slst1, bottom -> next -> value);
				removeSkipList(slst2, bottom -> next ->  value);
			}
			else
				removeSkipList(slst2, bottom -> next -> value);
				bottom = bottom -> next;
	}
}








