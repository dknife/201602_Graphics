#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

// parameters for camera lens
float range = 1.0;
float aspRatio = 1.0;
float dX=0.0;

void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspRatio * range + dX, aspRatio * range + dX, -range, range, -2, 2);
}

void reshape(int w, int h) {
	aspRatio = float(w) / h;
	SetCamera();
	glViewport(0, 0, w, h);	
}

void keyboard(unsigned char c, int, int) {
	if (c == 'w') range *= 0.9; 
	if (c == 's') range *= 1.1;
	if (c == 'a') dX -= 0.1;
	if (c == 'd') dX += 0.1;
	SetCamera();
	glutPostRedisplay();
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
	//glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glClearColor(1, 1, 1, 1);

	glutMainLoop();
	return 1;
}