#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

// parameters for camera lens
float aspRatio = 1.0;

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

void drawSphere(float radius) {
	glutWireSphere(radius, 6, 6);
	glLineWidth(4);
	drawAxes(radius);
	glLineWidth(1);
}

void display() {

	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//draw axes
	drawAxes(1.0);

	// angles .....
	static float mercuryAngle = 0.0;
	static float mercurySpin = 0.0;
	static float earthAngle = 0.0;
	static float earthSpin = 0.0;
	static float moonAngle = 0.0;
	static float jupiterAngle = 0.0;
	static float jupiterSpin = 0.0;
	static float jMoon1Angle = 0.0;
	static float jMoon2Angle = 0.0;

	// sun
	glColor3f(1.0, 0.3, 0.3);
	drawSphere(1.0);

	// mercury
	glPushMatrix();
		glColor3f(0.3, 0.3, 1.0);
		glRotatef(mercuryAngle, 0, 1, 0); mercuryAngle += 1;
		glTranslatef(3.0, 0.0, 0.0);
		glRotatef(mercurySpin, 0, 1, 0); mercurySpin += 7.32;
		drawSphere(0.3);
	glPopMatrix();

	// earth
	glPushMatrix();
		glColor3f(0.3, 0.7, 1.0);
		glRotatef(earthAngle, 0, 1, 0); earthAngle += 1.23;
		glTranslatef(4.0, 0.0, 0.0);
		glPushMatrix(); 
			glRotatef(earthSpin, 0, 1, 0); earthSpin += 21.3;
			drawSphere(0.4);
		glPopMatrix();
	

		// moon
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(moonAngle, 0, 1, 0); moonAngle += 4.12;
		glTranslatef(0.6, 0.0, 0.0);
		drawSphere(0.1);
	glPopMatrix();

	// Jupiter
	glPushMatrix();
		glColor3f(1.0, 0.5, 0.2);
		glRotatef(jupiterAngle, 0, 1, 0); jupiterAngle += 0.7;
		glTranslatef(6, 0, 0);
		glPushMatrix();
			glRotatef(jupiterSpin, 0, 1, 0); jupiterSpin += 5.1;
			drawSphere(0.6);
		glPopMatrix();

		// jMoon 1
		glPushMatrix();
			glColor3f(1, 1, 0);
			glRotatef(jMoon1Angle, 0, 1, 0); jMoon1Angle += 20.32;
			glTranslatef(1.0, 0.0, 0.0);
			drawSphere(0.1);
		glPopMatrix();

		// jMoon 2
		glPushMatrix();
			glColor3f(1, 1, 0);
			glRotatef(jMoon2Angle, 1, 0, 0); jMoon2Angle += 5.32;
			glTranslatef(0.0, 1.0, 0.0);
			drawSphere(0.1);
		glPopMatrix();

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