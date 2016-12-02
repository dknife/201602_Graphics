#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

#define TEXSIZE 16
GLubyte myTex[TEXSIZE][TEXSIZE][3];

void CreateTexture(void) {
	for (int i = 0; i < TEXSIZE; i++) {
		for (int j = 0; j < TEXSIZE; j++) {
			for (int k = 0; k < 3; k++) {
				myTex[i][j][0] = rand()%256;
				myTex[i][j][1] = rand() % 256;
				myTex[i][j][2] = rand() % 256;
			}
		}
	}	
}

void SetupTexture(void) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXSIZE, TEXSIZE, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, &myTex[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-1.0, 1.0, 0.0);
		glTexCoord2f(0, 0);
		glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(1, 0);
		glVertex3f(1.0, -1.0, 0.0);
		glTexCoord2f(1, 1);
		glVertex3f(1.0, 1.0, 0.0);
	glEnd();
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
	
	glutMainLoop();

	return 0;
}