#include <stdio.h>

#include "vector2f.h"

int main(void) {
	
	vector2f v1, v2, v3;
	setVector2f(&v1, 0, 0);
	setVector2f(&v2, 1, 0);
	setVector2f(&v3, 1, 1);
	float A = area2D(v1, v2, v3);
	printf("area = %f\n", A);


	return 1;
}