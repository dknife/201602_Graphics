#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
	srand((unsigned int)time(NULL));
	int nugu[3];

	for (int i = 0; i < 1; i++){
		nugu[i] = rand() % 20 + 5;
		printf("�а� ȫ�� UCC ������ ��� >>> %d\n", nugu[i]);
	}
}