#include <stdio.h>

#include "vector2f.h"

int main(void) {
	
	vector2f v1, v2;
	setVector2f(&v1, 1, 2);
	setVector2f(&v2, -1, 2);
	vector2f v3;
	addVector2f(&v3, v1, v2);
	printVector2f(v3);
	subVector2f(&v3, v1, v2);
	printVector2f(v3);
	float dot = dotProduct(v1, v2);
	printf("dot product = %f\n", dot);

	return 1;
}