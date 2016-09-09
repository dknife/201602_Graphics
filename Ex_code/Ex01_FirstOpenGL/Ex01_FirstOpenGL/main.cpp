#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(5);	
	glBegin(GL_POINTS);	
	
	for (float x = -1.0; x <= 1.0; x += 0.01) {
		float y = x*x;
		glColor3f(0, y, 0);
		glVertex3f(x, y, 0);
	}
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

	// 공통작업
	glClearColor(1, 1, 1, 1);

	// 메인 루프 
	glutMainLoop();
	return 1;
}