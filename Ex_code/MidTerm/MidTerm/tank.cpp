#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

#define CarWidth 8.0
#define CarLength 8.0
#define CarHeight 1.0
#define WheelRadius 1.5
#define TurretWidth 1.5
#define TurretHeight 2.0
#define TurretLength 3.0
#define BarrelWidth 0.5
#define BarrelLength 5.0


float carZ = 0.0;
float carZToAngle = 100.0;
float turretAngle = 0.0;
float barrelAngle = 0.0;
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
	case 'w': carZ -= 0.1; break;
	case 's': carZ += 0.1; break;
	case 'a': turretAngle += 1; break;
	case 'd': turretAngle -= 1; break;
	case 'i': barrelAngle += 1; break;
	case 'k': barrelAngle -= 1; break;
	case 'v': bPers = bPers ? false : true; SetCamera(); break;
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
}

void drawCircle(float radius, int nPoints) {
	glPushMatrix();
	glScalef(1.0, radius, radius);
	float angle;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < nPoints; i++) {
		angle = (6.28*i)/float(nPoints);
		glVertex3f(0, cos(angle), sin(angle));
	}
	glEnd();
	glPopMatrix();
}

void display() {


	// world
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 10, carZ + 10, 0, 0, carZ, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLineWidth(1);
	//draw axes
	drawAxes(1.0);

	// draw plane
	drawPlane(100, 0.5);

	glLineWidth(3);

	glTranslatef(0, 0, carZ);

	glColor3f(1, 0, 1);
	glTranslatef(0, WheelRadius, 0);
	drawBox(CarWidth, CarHeight, CarLength);
	
	// wheels 
	glPushMatrix();
		glPushMatrix();
		glTranslatef(CarWidth/2.0,0, CarLength / 2.0 - WheelRadius);
		glRotatef((carZ*carZToAngle), 1, 0, 0);
		drawCircle(WheelRadius, 6);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-CarWidth / 2.0, 0, CarLength / 2.0 - WheelRadius);
		glRotatef((carZ*carZToAngle), 1, 0, 0);
		drawCircle(WheelRadius, 6);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(CarWidth / 2.0, 0, -CarLength / 2.0 + WheelRadius);
		glRotatef((carZ*carZToAngle), 1, 0, 0);
		drawCircle(WheelRadius, 6);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-CarWidth / 2.0, 0, -CarLength / 2.0 + WheelRadius);
		glRotatef((carZ*carZToAngle), 1, 0, 0);
		drawCircle(WheelRadius, 6);
		glPopMatrix();
	glPopMatrix();
	
	// Turret and Barrel
	glPushMatrix();
		glTranslatef(0.0, CarHeight/2.0+TurretHeight/2.0, 0.0);
		glRotatef(turretAngle, 0, 1, 0);
		drawBox(TurretWidth, TurretHeight, TurretLength);

		glPushMatrix();
		glTranslatef(0.0, 0.0, -TurretLength / 2.0);
		glRotatef(barrelAngle, 1, 0, 0);
		glTranslatef(0.0, 0.0, -BarrelLength / 2.0);
		drawBox(BarrelWidth, BarrelWidth, BarrelLength);
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