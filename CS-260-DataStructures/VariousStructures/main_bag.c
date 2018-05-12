#include "listbag.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*Function to get number of milliseconds elapsed since program started execution*/
double getMilliseconds() {
   return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){
  if(argc== 2)
    {
		 int *dumb;
		struct bag* b = (struct bag*)malloc(sizeof(struct bag));/*Create new bag*/
		 initBag(b);/*Initialize*/
		 
		 char *s = argv[1];
      int n = atoi(s);/*number of elements to add*/
		 int i;
		 
		 for( i = 0 ; i < n; i++)
			addToBag(b, (TYPE)i);/*Add elements*/
		 
		 printf("The value at the front of the list is.. %d \n", frontList(b -> l));
		 printf("The value at the back of the list is.. %d \n", backList(b -> l));
		 printf("Popping data off the front \n\n"); 
		 removeFrontList(b -> l);
		 
		 printf("The value at the front of the list is.. %d \n", frontList(b -> l));
		 printf("The value at the back of the list is.. %d \n", backList(b -> l));
		 printf("Popping data off the back \n\n");
		 removeBackList(b -> l);
		 
		 printf("The value at the front of the list is.. %d \n", frontList(b -> l));
		 printf("The value at the back of the list is.. %d \n", backList(b -> l));
		 printf("Removing '3' from the bag \n \n");
		 removeFromBag(b,3);
		 
		 struct DLink *holder = b -> l -> head -> next;
		 b -> l -> head -> next = holder;
		 
		 for (i =1 ; i< b -> l -> size +1; i++){
			 printf ("At link # %d the value is: %d \n",i,  b -> l -> head -> next -> value);
			 b -> l -> head -> next = b -> l -> head -> next -> next;
			}
		 
		 b -> l -> head -> next = holder;
		 
		 printf("Searching for '4'.. \n\n");
		double t1 = getMilliseconds();/*Time before contains()*/
      bagContains(b, (TYPE)4);
      double t2 = getMilliseconds();/*Time after contains()*/
		printf("Iteratively it took.. %g\n", t2-t1);
		 
		 t1 = t2 = 0;
		 printf("Searching for '5'.. \n\n");
		 t1 = getMilliseconds();
		 if (_contains_recursive(b -> l -> head -> next, 5) == 1)
			 _remove_recursive(b -> l, b -> l -> head -> next, 5, dumb);
		 t2 = getMilliseconds();
		 printf(" Recursively it took.. %g\n", t2-t1);
		 
		 
		 b -> l -> head -> next = holder;
		 freeBag(b);
		 
		 listRemove(b -> l, 5);
    }
  else
    printf("Please enter the number of elements to add.\n");

  return 0;

}

