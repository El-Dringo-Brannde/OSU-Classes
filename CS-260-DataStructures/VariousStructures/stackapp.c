#include <stdio.h>
#include <stdlib.h>


#define TYPE char
struct DynArr
{
	TYPE *data;             /* pointer to the data array */
	int size;               /* Number of elements in the array */
	int capacity;           /* capacity of the array */
};
typedef struct DynArr DynArr;



int isEmptyArr(DynArr *v);
void pushArr(DynArr *v, TYPE val);
TYPE topArr(DynArr *v);
void popArr(DynArr *v);




void pushArr(DynArr *v, TYPE val)       {
	int i = v -> size;
	
	v -> data[i] = val;
	v -> size++;
}
void popArr(DynArr *v)  {
	int i = (v -> size -1);
	v -> data[i] = 'd';
	v -> size--;
}


TYPE topArr(DynArr *v){
	TYPE holder;
	int i = 0;
	
	while (v -> data[i] != 'd')
		i++;
	
	holder = v -> data[i - 1];
	return holder;
}

char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return 0;
	else
		return c;
}




int isBalanced(char *s){
	DynArr *array = (DynArr *) malloc (sizeof(DynArr));
	array -> data = (TYPE *) malloc (sizeof(TYPE) * 100);
	array -> size = 0;
	array -> capacity = 100;
	
	int i = 0;
	for (i = 0; i < 100; i++)
		array -> data[i] = 'd';
	
	char temp;
	char top;

	do {
		temp = nextChar(s);
		if (temp == '(')
			pushArr(array, '(');
		if (temp == '{')
			pushArr(array, '{');
		if (temp == '[')
			pushArr(array, '[');
		
		if (temp == ')'){
			top = topArr(array);
			if (top != '('){
				return 0;
			}
			else{
				popArr(array);
			}
		}
		if (temp == '}'){
			top = topArr(array);
			if (top != '{'){
				return 0;
			}
			else{
				popArr(array);
			}
		}
		if (temp == ']'){
			top = topArr(array);
			if (top != '['){
				return 0;
			}
			else{
				popArr(array);
			}
		}
		if (array -> size == 0)
			break;
		
	}while(temp != 0);
		
	if (array -> size != 0)
		return 0;
	
	
	return 1;
}


int main(int argc, char* argv[]){
	
	printf("Assignment 2\n");
	
	char *s =argv[1];
	int res;
	
	res = isBalanced(s);
	
	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);
	
	return 0;
}

