#include "vector2f.h"
#include <stdio.h>

void setVector2f(vector2f *v, float x, float y) {
	v->x = x;
	v->y = y;
}

void printVector2f(vector2f v) {
	printf("vect2f: (%f %f)\n", v.x, v.y);
}

void addVector2f(vector2f *res, vector2f v1, vector2f v2) {
	res->x = v1.x + v2.x;
	res->y = v1.y + v2.y;
}

void subVector2f(vector2f *res, vector2f v1, vector2f v2) {
	res->x = v1.x - v2.x;
	res->y = v1.y - v2.y;
}

float dotProduct(vector2f v1, vector2f v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

float crossProduct(vector2f v1, vector2f v2) {
	return v1.x*v2.y - v1.y*v2.x;
}