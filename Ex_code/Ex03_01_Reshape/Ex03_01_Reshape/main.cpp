#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

// circle drawing function

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float asp = float(w) / h;
	glOrtho(-asp * 2, asp*2, -2, 2, -2, 2);
	glViewport(0,0, w, h);
}

void drawCircle(
	float radius, float dx, float dy, int nPoints = 100) {
	float angle = 0.0;
	float twopi = 3.14*2.0;
	float angleStep = twopi / nPoints;

	glBegin(GL_POLYGON);
	// vertices
	for (int i = 0; i < nPoints; i++) {
		glVertex3f(radius*cos(angle) + dx, radius*sin(angle) + dy, 0);
		angle += angleStep;
	}
	glEnd();
}

void display() {

	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.25, 0.0);
	glVertex3f(0.5, -0.25, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glColor3f(0, 1, 0);
	glVertex3f(0.5, 0.25, 0.0);
	glVertex3f(0.9, 0.5, 0.0);
	glVertex3f(0.8, 0.5, 0.0);
	glVertex3f(0.4, 0.25, 0.0);
	glEnd();

	drawCircle(0.25, -0.25, -0.25, 10);
	drawCircle(0.15, 0.25, -0.25, 5);

	glutSwapBuffers();

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("I Love Graphics");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glClearColor(1, 1, 1, 1);

	glutMainLoop();
	return 1;
}