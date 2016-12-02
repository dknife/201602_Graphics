#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>

#define TEXSIZE 64
GLubyte myTex[TEXSIZE][TEXSIZE][3];

void CreateTexture(void) {
	for (int i = 0; i < TEXSIZE; i++) {
		for (int j = 0; j < TEXSIZE; j++) {
			for (int k = 0; k < 3; k++) {
				float x = float(i) / (TEXSIZE - 1) - 0.5;
				float y = float(j) / (TEXSIZE - 1) - 0.5;
				GLubyte v = 255 * ((sin(10.0*x)*cos(10.0*y) + 1.0) / 2.0);
				myTex[i][j][0] = v;
				myTex[i][j][1] = (v*v) % 255;
				myTex[i][j][2] = v;
			}
		}
	}
}

void SetupTexture(void) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXSIZE, TEXSIZE, 0,
		GL_RGB, GL_UNSIGNED_BYTE, &myTex[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
}

void myDisplay() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);


	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	static float t = 0.0;
	glTranslatef(t, 0, 0);
	t += 0.01;
	glBegin(GL_QUADS);
	glTexCoord2f(0, 2);
	glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(2, 0);
	glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(2, 2);
	glVertex3f(1.0, 1.0, 0.0);
	glEnd();
	glMatrixMode(GL_MODELVIEW);

	glutSwapBuffers();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	CreateTexture();
	SetupTexture();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("My Texture");

	init();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);

	glutMainLoop();

	return 0;
}