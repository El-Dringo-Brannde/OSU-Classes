#ifndef MAIN_C
#define MAIN_C

/*	dynArr.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

/* ************************************************************************
	Dynamic Array Functions
 ************************************************************************ */

/*			initialize the array
 
 Initialize (including allocation of data array) dynamic array.
 
	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
 */
void initDynArr(DynArr *v, int capacity)
{
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	
	v->size = 0;
	v->capacity = capacity;
}

/*		allocates the array
 
 Allocate and initialize dynamic array.
 
	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
 and 0 elements in it.
 */
DynArr* newDynArr(int cap)
{
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/*		free's memory of the array data
 Deallocate data array in dynamic array.
 
	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
 */
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/*		free the array of structs
 Deallocate data array and the dynamic array ure.
 
	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
 */
void deleteDynArr(DynArr *v)	{
	
	freeDynArr(v);
	free(v);
	v = NULL;
}

/*			Set's the new capacity for the array
 
 Resizes the underlying array to be the size cap
 
	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
 */
void _dynArrSetCapacity(DynArr *v, int newCap)	{
	
	newCap = (2 * v -> capacity);
	int tempsize = v -> size;
	int i = 0;
	
	DynArr *temparray = (DynArr *) malloc (sizeof(DynArr));
	printf("The capacity prior to the re-size is.. %d \n", v -> size + 1);
	
	initDynArr(temparray, newCap);
	
	for (i = 0; i < tempsize; i++)
		temparray -> data[i] = v -> data[i];
	
	for (i = tempsize; i < newCap; i++)
		temparray -> data[i] = 0;
	
	printf("The new capacity is.. %d \n", newCap);
	
	for (i = 0; i < newCap; i++)
		printf("%d \n", temparray -> data[i]);
	
	deleteDynArr(v);
	
	v = newDynArr(newCap);
	
	for (i = 0; i < tempsize; i++) {
		v -> data[i] = temparray -> data[i];
		v -> size++;
	}
	for ( i = tempsize; i < newCap; i++)
		v -> data[i] = 0;
	
	deleteDynArr(temparray);
}

/*		tell's size of dynamic array
 Get the size of the dynamic array
 
	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
 */
int sizeDynArr(DynArr *v)	{
	return v->size;
}

/*			add an element to the array
	
 Adds an element to the end of the dynamic array
 
	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
 */
void addDynArr(DynArr *v, TYPE val)	{
	
	int tempsize = v ->size;
	
	v -> data[tempsize] = val;
	v -> size++;
}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
 */
TYPE getDynArr(DynArr *v, int pos)	{
	int temp = 0;
	
	temp = v -> data[pos];
	return temp;
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there
 
	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
 */
void putDynArr(DynArr *v, int pos, TYPE val)
{	v -> data[pos] = val;	}


/*	Swap two specified elements in the dynamic array
 
	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
 */
void swapDynArr(DynArr *v, int i, int  j)	{
	int temp = v -> data[i];
	v ->data[i] = v -> data[j];
	v ->data[j] = temp;
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap
 
	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
 */
void removeAtDynArr(DynArr *v, int idx) {
	int tempsize = v -> size;
	
	int i = idx;
	int j = i+1;
	for (i = idx; i < (tempsize - 1); i++) {
		v -> data[i] = v -> data[j];
		j++;
	}
	
	v ->size--;
}

/* ************************************************************************
	Stack Interface Functions
 ************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the
	dynamic array stack has an item on it.
 
	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
 */
int isEmptyDynArr(DynArr *v)	{
	if (v -> size == 0) {
		printf("The array is empty my friend!");
		return 1;
	}
	else
		return 0;
}

/* 	Push an element onto the top of the stack
 
	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
 if reached capacity, capacity is doubled
 val is on the top of the stack
 */
void pushDynArr(DynArr *v, TYPE val)	{
	int i = 0;
	
	if (v -> size >= v -> capacity)
		_dynArrSetCapacity(v, (v -> size * 2));
	
	v -> data[0] = 3;
	while (v -> data[i] != 0)
		i++;
	printf("Now let's push '30' onto the top of the 'stack' \n");
	
	v -> data[i] = val;
	v -> size++;
	printf("Now the array looks like.. \n");
	for (i = 0; i < v -> size; i++)
		printf("%d \n",v -> data[i]);
	
}

/*	Returns the element at the top of the stack
 
	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
 */
TYPE topDynArr(DynArr *v)	{
	int hold = 0;
	int i = 0;
	
	v -> data[0] = 3;
	
	while (v -> data[i] != 30)
		i++;
	
	hold = v -> data[i];
	
	return hold;
}

/* Removes the element on top of the stack
 
	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
 the top has been removed
 */
void popDynArr(DynArr *v)	{
	int i = (v -> size - 1);
	printf("Let's remove the top item which is.. %d \t", v -> data[i]);
	v -> data[i] = 0;
	v -> size--;
	printf("\n");
}

/* ************************************************************************
	Bag Interface Functions
 ************************************************************************ */

/*			tells if value is in the array
 
 Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
 
	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
 */
int containsDynArr(DynArr *v, TYPE val)	{
	int i = 0;
	
	printf("Searching.. \n");
	
	for (i = 0; i < v -> capacity; i++)
		if (val == v -> data[i])
			return i;
	
	return -1;
}

/*		delete value from array if there
 Removes the first occurrence of the specified value from the collection
	if it occurs
 
	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
 */
void removeDynArr(DynArr *v, TYPE val)
{
	int index = containsDynArr(v,val);
	removeAtDynArr(v,index);
}


/*
	Demonstrates the dynamic array stuff
 */
DynArr *dynarraystuff(int i, int cap, DynArr *array)	{
	
	array = newDynArr(cap);
	printf("Writing to the array for the first time.. \n");
	
	for (i = 0; i < cap; i++)
		addDynArr(array,i);
	
	printf("The size of the array is %d \n", sizeDynArr(array));
	
	printf("The data of the array is.. \n");
	for (i = 0; i < cap; i++)
		printf("%d \n", array -> data[i]);
	
	printf("The array at element '1' is.. \n");
	printf("%d \n", getDynArr(array, 1));
	
	printf("Changing the value at position '3' for 500 \n");
	putDynArr(array, 3, 500);
	
	for (i = 0; i < cap; i++)
		printf("%d \n", array -> data[i]);
	
	
	printf("Swapping the values in the array at '1' & '3' \n");
	swapDynArr(array, 1, 3);
	for (i = 0; i < cap; i++)
		printf("%d \n", array -> data[i]);
	
	printf("Now let's remove the data in the array at position '1' then shift the rest over\n");
	removeAtDynArr(array,1);
	for (i = 0; i < array ->size; i++)
		printf("%d \n", array -> data[i]);
	
	printf("Resizing the array now! \n");
	_dynArrSetCapacity(array, array-> size);
	
	printf("The overall size of the array is.. %d \n", sizeDynArr(array));
	return array;
}

/*
	Made to demonstrate the functionality of the 'stack' functions
 */
void stackstuff(DynArr *array, int i){
	isEmptyDynArr(array);
	
	pushDynArr(array, 30);
	
	printf("The data sitting at the top of the stack is.. %d \n", topDynArr(array));
	
	popDynArr(array);
	
	printf("Now the array looks like this\n ");
	for (i = 0; i < array -> size; i++)
		printf("%d \n", array -> data[i]);
	
	
}

/*
	Made to demonstrate the funcionality of the 'bag'
 */
void bagstuff(DynArr *array){
	int holder = 0;
	printf("What number do you want to search for? \t");
	scanf("%d", &holder);
	
	if (containsDynArr(array, holder) == -1)
		printf("The value wasn't found, I'm sorry! \n");
	else {
		printf("Now let's remove that silly thing! \n");
		removeDynArr(array,holder);
	}
	
	printf ("Now the array looks something like.. \n");
	int i = 0;
	for (i = 0; i < array -> size; i++)
		printf("%d \n", array -> data[i]);
}




/*
	Merely here for testing
 
 int main(){
	int cap = 5;
	int i;
	DynArr *array = 0;
 
	array = dynarraystuff(i,cap,array);
	stackstuff(array, i);
	bagstuff(array);
	
	return 0;
 }
 */






#endif









