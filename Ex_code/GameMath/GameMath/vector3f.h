#ifndef _vec3fymkang_hh_
#define _vec3fymkang_hh_

struct vector3f {
	float x;
	float y;
	float z;
};

// �Լ����� ������ ��������.
void setVector3f(vector3f *v, float x, float y, float z);
void printVector3f(vector3f v);
void addVector3f(vector3f *res, vector3f v1, vector3f v2);
void subVector3f(vector3f *res, vector3f v1, vector3f v2);
float dotProduct(vector3f v1, vector3f v2);
void  crossProduct(vector3f *res, vector3f v1, vector3f v2);
float area3D(vector3f v1, vector3f v2, vector3f v3);

#endif
