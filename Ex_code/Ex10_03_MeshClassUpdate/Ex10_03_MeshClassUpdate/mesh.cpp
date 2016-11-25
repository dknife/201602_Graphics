#include "mesh.h"

CMesh::CMesh() { }

CMesh::~CMesh() {
	delete[] verts;
}

void CMesh::computeNormals() {
	 
}

vertex CMesh::computeNormal(vertex a, vertex b, vertex c) {
	vertex normal;
	vertex u, v;
	u.x = b.x - a.x; u.y = b.y - a.y; u.z = b.z - a.z;
	v.x = c.x - a.x; v.y = c.y - a.y; v.z = c.z - a.z;
	normal.x = u.y * v.z - u.z * v.y;
	normal.y = u.x * v.z - u.z * v.x;
	normal.z = u.x * v.y - u.y * v.x;
	float len = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
	normal.x /= len;
	normal.y /= len;
	normal.z /= len;
	return normal;
}

void CMesh::read(char *fname) {
	FILE *f;
	fopen_s(&f, fname, "r");
	if (!f) { printf("file not found\n"); return; }

	fscanf(f, "%d", &nV);
	verts = new vertex[nV];
	norms = new vertex[nV];
	for (int i = 0; i < nV; i++) {
		fscanf(f, "%f", &verts[i].x);
		fscanf(f, "%f", &verts[i].y);
		fscanf(f, "%f", &verts[i].z);
	}
	fscanf(f, "%d", &nF);
	tris = new triangle[nF];
	for (int i = 0; i < nF; i++) {
		fscanf(f, "%d", &tris[i].v0);
		fscanf(f, "%d", &tris[i].v1);
		fscanf(f, "%d", &tris[i].v2);
	}

	computeNormals();
}

void CMesh::show() {
	
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nF; i++) {
		
		 // current face = tris[i]
		 // three vertices : tris[i].v0, v1, v2
		int v0 = tris[i].v0;
		int v1 = tris[i].v1;
		int v2 = tris[i].v2;
		vertex normal = computeNormal(verts[v0], verts[v1], verts[v2]);
		glNormal3f(normal.x, normal.y, normal.z);
		glVertex3f(verts[v0].x, verts[v0].y, verts[v0].z);
		glVertex3f(verts[v1].x, verts[v1].y, verts[v1].z);
		glVertex3f(verts[v2].x, verts[v2].y, verts[v2].z);
		
		
	}
	glEnd();
	
}
