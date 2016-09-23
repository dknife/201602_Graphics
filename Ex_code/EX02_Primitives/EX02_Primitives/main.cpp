#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);


	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.25, 0.0);
	glVertex3f( 0.5, -0.25, 0.0);
	glVertex3f( 0.5, 0.5, 0.0);
	glColor3f(0, 1, 0);
	glVertex3f( 0.5, 0.25, 0.0);
	glVertex3f( 0.9, 0.5, 0.0);
	glVertex3f( 0.8, 0.5, 0.0);
	glVertex3f( 0.4, 0.25, 0.0);
	glEnd();

	int nPoints = 100;
	float angle = 0.0;
	float twopi = 3.14*2.0;
	float angleStep = twopi / nPoints;
	float radius = 0.25;
	float dx = 0.0;
	float dy = -0.25;

	glBegin(GL_POLYGON);
	// vertices
	for (int i = 0; i < nPoints; i++) {
		glVertex3f(radius*cos(angle) + dx, radius*sin(angle) + dy, 0);
		angle += angleStep;
	}
	glEnd();




	/*
	float angle=0;
	float nPoints = 100;
	float step = 3.141592*2.0 / nPoints;
	float radius = 0.25;
	float dx = 0;
	float dy = -0.25;
	glBegin(GL_POLYGON);
	for (int i = 0; i < nPoints; i++) {
		float c = radius * cos(angle);
		float s = radius * sin(angle);
		glVertex3f(c+dx, s+dy, 0);
		angle += step;
	}
	glEnd();*/

	glFlush();

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("I Love Graphics");
	glutDisplayFunc(display);

	glClearColor(1, 1, 1, 1);

	glutMainLoop();
	return 1;
}
