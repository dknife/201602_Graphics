#include <stdio.h>

#include "vector3f.h"

int main(void) {
	
	vector3f p1, p2, p3;
	setVector3f(&p1, 0, 0, 0);
	setVector3f(&p2, 1, 0, 0);
	setVector3f(&p3, 1, 1, 0);
	float A = area3D(p1, p2, p3);
	printf("area = %f\n", A);


	return 1;
}