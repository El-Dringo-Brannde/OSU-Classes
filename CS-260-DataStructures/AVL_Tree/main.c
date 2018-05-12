#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "avl.h"

/* find minimum-cost path */
/* Input: pointer to tree
 pointer to array that should store all node values from
 root to leaf along the identified min-cost path,
 Output: min-cost path length
 */
int FindMinPath(struct AVLnode *root, int *path)
{
	
	/* I'm assuming that we are supposed to find the lowest number cost, not the amount of nodes we traveled */
	struct AVLnode * cur = root;
	printf("test: %d \n", cur  -> left -> val);
	
	assert (cur != NULL);
	
	int i = 0; /* counts the number of nodes along a path */
	
	while (cur != 0){
		if (cur -> right != NULL){
			int righty = cur -> right ->  val;
			if (cur -> right -> left == NULL){
				if (cur -> left != NULL && cur -> left -> left != NULL){
					if (cur -> right -> val  <= cur -> left -> val + cur -> left -> left -> val){
						printf("Checking left + left: %d \n", cur -> val);
						path[i] = cur -> val;
						i++;
						path[i] = righty;
						i++;
						break;
					}
				}
			}
			
			else if (cur -> right -> left != NULL && cur -> right != NULL && cur -> left != NULL){
				int leftofright = cur -> right -> left -> val;
				int checker = righty + leftofright;
				if (checker <= cur -> left -> val){
					printf("Checking Right + left: %d \n", cur -> val);
					path[i] = cur -> val;
					cur = cur -> right;
					i++;
				}
			}
		}
		path[i] = cur -> val;
		cur = cur -> left;
		i++;
		
	}
	
		//printf("Bottom: %d \n", path[i -1]);
	return i;
}

int main()
{
	const char *filename = "input.txt";
	FILE *file;
	int num, len, i;
	clock_t timer;
	int pathArray[50];
	
	struct AVLTree *tree = newAVLTree(); /*return an empty tree */
	
	file = fopen(filename, "r");
	assert(file != 0);
	
	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){
		addAVLTree(tree, num);
	}
	
	timer = clock();
	
	/* Find the minimum-cost path in the AVL tree*/
	pathArray[0] = tree->root->val;
	struct AVLnode *root = tree -> root;
	len = FindMinPath(root, pathArray);
	
	/* Print out all numbers on the minimum-cost path */
	printf("The minimum-cost path is: ");
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");
	
	fclose(file);
	timer = clock() - timer;
	printf("\nExecution time is %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	deleteAVLTree(tree);
}



