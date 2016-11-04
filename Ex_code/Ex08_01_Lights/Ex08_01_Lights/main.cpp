#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#include "Camera.h"
#include "Light.h"

#include <math.h>

void reshape(int w, int h) {
	float asp = float(w) / h;
	setCameraLens(60, asp);
	glViewport(0, 0, w, h);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	static float angle = 0.0;
	setCameraPosition(cos(angle), 1.5, sin(angle));
	angle += 0.01;

	SetLightPosition(1, 1, 1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	for (float x = -1.0; x <= 1.0; x += 0.1) {
		for (float z = -1.0; z <= 1.0; z += 0.1) {
			glPushMatrix();
			glTranslatef(x, 0, z);
			glutSolidTeapot(0.1);
			glPopMatrix();
		}
	}

	glutSwapBuffers();
}

void init() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	SetMaterial(1.0, 1.0, 0.0);
	SetLight(1.0, 1.0, 1.0);	
}

int main(int argc, char **argv) {
	// glut initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Lighting Test");

	// initialization
	init();

	// callback registration
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);

	// enter mainloop
	glutMainLoop();
}