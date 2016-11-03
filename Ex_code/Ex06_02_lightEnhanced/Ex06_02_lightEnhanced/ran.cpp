#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
	srand((unsigned int)time(NULL));
	int nugu[3];

	for (int i = 0; i < 1; i++){
		nugu[i] = rand() % 20 + 5;
		printf("ÇÐ°ú È«º¸ UCC Á¦ÀÛÆÀ ¸â¹ö >>> %d\n", nugu[i]);
	}
}