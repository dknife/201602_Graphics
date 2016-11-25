#ifndef _mesh_2016_ymkang_hh_
#define _mesh_2016_ymkang_hh_ 

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>

#define fscanf fscanf_s

struct vertex {
	float x, y, z;
};

class CMesh {
	// properties
	int nV;
	vertex *verts;
	// methods
public:
	CMesh();
	~CMesh();
	void read(char *fname);
	void show();
};

#endif