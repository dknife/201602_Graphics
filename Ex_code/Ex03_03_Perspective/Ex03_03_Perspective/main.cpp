#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

// parameters for camera lens
float range = 1.0;
float aspRatio = 1.0;
float dX = 0.0;

void SetCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-aspRatio * range + dX, aspRatio * range + dX, -range, range, -2, 2);
	gluPerspective(60, aspRatio, 0.1, 1000);
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
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	static float angle = 0.0;
	glRotatef(angle, 0, 1, 0);
	angle += 1;

	glColor3f(1, 0, 0);
	for (float z = 0.0; z < 1.0; z += 0.1) {
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.5, 0.5, -z);
		glVertex3f(-0.5, -0.5, -z);
		glVertex3f(0.5, -0.5, -z);
		glVertex3f(0.5, 0.5, -z);
		glEnd();
	}
	

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
	glutKeyboardFunc(keyboard);

	glClearColor(1, 1, 1, 1);

	glutMainLoop();
	return 1;
}