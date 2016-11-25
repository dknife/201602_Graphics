#include "mesh.h"

CMesh::CMesh() { }

CMesh::~CMesh() {
	delete[] verts;
}

void CMesh::read(char *fname) {
	FILE *f;
	fopen_s(&f, fname, "r");
	if (!f) { printf("file not found\n"); return; }

	fscanf(f, "%d", &nV);
	verts = new vertex[nV];
	for (int i = 0; i < nV; i++) {
		fscanf(f, "%f", &verts[i].x);
		fscanf(f, "%f", &verts[i].y);
		fscanf(f, "%f", &verts[i].z);
	}

}

void CMesh::show() {
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	for (int i = 0; i < nV; i++) {
		glVertex3f(verts[i].x, verts[i].y, verts[i].z);
	}
	glEnd();
}
