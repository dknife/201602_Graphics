#ifndef _vec2f_ymkang_hh
#define _vec2f_ymkang_hh

struct vector2f {
	float x;
	float y;
};

// 함수들의 원형을 정의하자.
void setVector2f(vector2f *v, float x, float y);
void printVector2f(vector2f v);
void addVector2f(vector2f *res, vector2f v1, vector2f v2);
void subVector2f(vector2f *res, vector2f v1, vector2f v2);
float dotProduct(vector2f v1, vector2f v2);

#endif
