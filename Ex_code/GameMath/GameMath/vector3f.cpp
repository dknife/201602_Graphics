#include "vector3f.h"
#include <stdio.h>

void setVector3f(vector3f *v, float x, float y, float z) {
	v->x = x; v->y = y; v->z = z;
}

void printVector3f(vector3f v) {
	printf("vec3f: (%f, %f, %f)\n", v.x, v.y, v.z);
}

void addVector3f(vector3f *res, vector3f v1, vector3f v2) {
	res->x = v1.x + v2.x;
	res->y = v1.y + v2.y;
	res->z = v1.z + v2.z;
}

void subVector3f(vector3f *res, vector3f v1, vector3f v2) {
	res->x = v1.x - v2.x;
	res->y = v1.y - v2.y;
	res->z = v1.z - v2.z;
}

float dotProduct(vector3f v1, vector3f v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

void  crossProduct(vector3f *res, vector3f v1, vector3f v2);
float area3D(vector3f v1, vector3f v2, vector3f v3);