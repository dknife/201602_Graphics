#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

bool bPers = true;

// parameters for camera lens
float aspRatio = 1.0;

void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	bPers ? gluPerspective(60, aspRatio, 0.1, 1000) : glOrtho(-10, 10, -10, 10, -100, 100);
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

void drawPlane(float width, float interval) {
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	for (float i = -width; i <= width; i += interval) {
		glVertex3f(i, 0, -width);
		glVertex3f(i, 0, width);
		glVertex3f(width, 0, i);
		glVertex3f(-width, 0, i);
	}
	glEnd();
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
	gluLookAt(0, 3, 3, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLineWidth(1);
	//draw axes
	drawAxes(1.0);

	// draw plane
	drawPlane(20, 0.5);

	

	glutSwapBuffers();

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

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);


	glutMainLoop();
	return 1;
}