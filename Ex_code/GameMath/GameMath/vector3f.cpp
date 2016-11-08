#include "vector3f.h"
#include <stdio.h>
#include <math.h>

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

float length(vector3f v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

void  crossProduct(vector3f *res, vector3f v1, vector3f v2) {
	res->x = v1.y * v2.z - v1.z * v2.y;
	res->y = v1.z * v2.x - v1.x * v2.z;
	res->z = v1.x * v2.y - v1.y * v2.x;
}

float area3D(vector3f v1, vector3f v2, vector3f v3) {
	vector3f u, v;
	subVector3f(&u, v2, v1);
	subVector3f(&v, v3, v1);
	vector3f cross;
	crossProduct(&cross, u, v);
	return length(cross) / 2.0;
}

void normalize(vector3f *v) {
	float len = length(*v);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}