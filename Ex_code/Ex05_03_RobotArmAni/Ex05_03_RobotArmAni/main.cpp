#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

// parameters for camera lens
float aspRatio = 1.0;
float armY=0, armZ=0, handZ=0;
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
	case 'y': armY += 1.0; break;
	case 'Y': armY -= 1.0; break;
	case 'z': armZ += 1.0; break;
	case 'Z': armZ -= 1.0; break;
	case 'h': handZ += 1.0; break;
	case 'H': handZ -= 1.0; break;
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

void drawBox(float xsize, float ysize, float zsize) {
	glPushMatrix();
	glScalef(xsize, ysize, zsize);
	glutWireCube(1.0);
	glPopMatrix();
	drawAxes(1.0);
}

void display() {


	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 3, 10, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//draw axes
	drawAxes(1.0);

	// draw plane
	drawPlane(10, 0.5);

	glColor3f(1, 0, 1);
	glTranslatef(0, 0.25, 0);
	drawBox(3, 0.5, 3);

	glColor3f(1, 1, 0);
	glTranslatef(0, 1.25, 0);
	glRotatef(armY, 0, 1, 0);
	drawBox(0.2, 2.0, 0.2);

	glColor3f(1, 1, 1);
	glTranslatef(0, 1.0, 0);
	glRotatef(armZ, 0, 0, 1);
	glTranslatef(0, 0.75, 0);
	drawBox(0.1, 1.5, 0.1);


	
	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	glRotatef(handZ, 0, 0, 1);
	glTranslatef(0, 0.25, 0);
	glColor3f(0, 1, 1);
	drawBox(0.1, 0.5, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	glRotatef(-handZ, 0, 0, 1);
	glTranslatef(0, 0.25, 0);
	glColor3f(0, 1, 1);
	drawBox(0.1, 0.5, 0.1);
	glPopMatrix();

	glutSwapBuffers();

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Xform");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 1;
}