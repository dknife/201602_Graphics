#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(5);
	glBegin(GL_POINTS);
		static float x = -1.0;
		float y = x*x;
		glColor3f(0, y, 0);
		glVertex3f(x, y, 0);
		x += 0.0001;
		if (x > 1.0) x -= 2.0;
	glEnd();

	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("I Love Graphics");
	glutDisplayFunc(display);
	glutIdleFunc(display);

	// common state
	glClearColor(1, 1, 1, 1);

	// go into the loop
	glutMainLoop();
	return 1;
}