#include <stdio.h>
#include "vector2f.h"
#include "vector3f.h"

int main(void) {
	
	vector3f v;
	setVector3f(&v, 1, 1, 1);

	normalize(&v);
	printVector3f(v);

	printf("length of normalized vector = %f\n", length(v));


	return 1;
}