#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>
#include "STBImage.h"

#define NTEXTURES 10
// void glGenTextures(int n, GLuint *textures)
// void glBindTexture(GLenum target /*GL_TEXTURE_2D*/, GLuint texture);
GLuint tex[NTEXTURES];
unsigned char *myTex=NULL;
int texWidth, texHeight, bitPerPixel;


void PrepareTextures(int n, GLuint *textures) {
	glGenTextures(n, textures);
	glEnable(GL_TEXTURE_2D);	
}

void SetTexture(int idx, char *fname) {
	if (myTex) delete[] myTex;
	glBindTexture(GL_TEXTURE_2D, tex[idx]);
	myTex = stbi_load(fname, &texWidth, &texHeight, &bitPerPixel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myTex);
	delete[] myTex; myTex = NULL;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
	
void drawQuad(void) {
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 0);
	glEnd();
}

void myDisplay() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,4, 0, 0, 0, 0, 1, 0);


	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);

	static float angle = 0;
	glTranslatef(-NTEXTURES*(sin(angle)+1.0), 0, 0);
	for (int i = 0; i < NTEXTURES; i++) {
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		glPushMatrix();
		glTranslatef(i*2, 0, 0);
		drawQuad();
		glPopMatrix();
	}
	angle += 0.01;
	
	glutSwapBuffers();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	PrepareTextures(10, tex);
	SetTexture(0, "dirty.jpg");
	SetTexture(1, "cosmos.jpg");
	SetTexture(2, "wood.jpg");
	SetTexture(3, "ice.jpg");
	SetTexture(4, "woodchips.jpg");
	SetTexture(5, "rock.jpg");
	SetTexture(6, "soil.jpg");
	SetTexture(7, "pororo.jpg");
	SetTexture(8, "robot.jpg");
	SetTexture(9, "dragon.jpg");
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("My Texture");

	init();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);

	glutMainLoop();

	return 0;
}