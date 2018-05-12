#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
	srand(time(NULL));
	int randomized;
	if (argc < 2){
		printf("Dammit, listen once and awhile");
		exit(1);
	}

	int i = 0,keylength = atoi(argv[1]);

	for(i = 0; i < keylength; i++){
		int j = rand() % 10;
			printf("%d", j);
	}
  printf("\n");
  return 0;
}
