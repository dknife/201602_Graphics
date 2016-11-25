#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>

#define fscanf fscanf_s

struct vertex {
	float x, y, z;
};

int nVertex=0;
vertex *verts;

void readMesh(char *fName) {
	FILE *f;
	fopen_s(&f, fName, "r");
	fscanf(f, "%d", &nVertex);
	verts = new vertex[nVertex];
	for (int i = 0; i < nVertex; i++) {
		fscanf(f, "%f", &verts[i].x);
		fscanf(f, "%f", &verts[i].y);
		fscanf(f, "%f", &verts[i].z);
	}
	
}
void showMesh(vertex *v, int n) {

	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	for (int i = 0; i < n; i++) {
		glVertex3f(v[i].x, v[i].y, v[i].z);
	}
	glEnd();
}

float aspRatio = 1.0;

//light parameters
GLfloat lit_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lit_position[] = { 5, 5, 0, 1 };
// material parameters
GLfloat mat_diffuse[] = { 1.0, 1.0, 0.5, 1.0 };

void SetLighting(void) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);

}

void SetLightPosition(void) {
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position);
}


void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspRatio, 0.1, 1000);
}

void reshape(int w, int h) {
	aspRatio = float(w) / h;
	SetCamera();
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char c, int, int) {
	switch (c) {
	case 27: exit(0);
	}
}

void drawAxes(float size) {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0); glVertex3f(size, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0); glVertex3f(0, size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0); glVertex3f(0, 0, size);
	glEnd();
}



void display() {


	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	static float angle = 0;
	gluLookAt(200.0*cos(angle), 3, 200.0*sin(angle), 0, 0, 0, 0, 1, 0);
	angle += 0.01;

	SetLightPosition();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLineWidth(1);
	//draw axes
	drawAxes(1.0);

	glEnable(GL_LIGHTING);

	// draw mesh
	showMesh(verts, nVertex);

	glDisable(GL_LIGHTING);

	glutSwapBuffers();

}


void init(void) {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	// light enable
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	SetLighting();

	readMesh("complex.sms");
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Light");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	init();


	glutMainLoop();
	return 1;
}