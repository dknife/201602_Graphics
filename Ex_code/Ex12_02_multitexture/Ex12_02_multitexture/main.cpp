#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/glut.h>

#include <math.h>
#include "STBImage.h"

#define NTEXTURES 2


GLuint tex[NTEXTURES];
unsigned char *myTex=NULL;
int texWidth, texHeight, bitPerPixel;


void PrepareTextures(int n, GLuint *textures) {
	glGenTextures(n, tex);
	glEnable(GL_TEXTURE_2D);	
}


GLuint LoadTexture(const char *filename) {
	unsigned char *image;

	int width, height, bPerPix;
	image = stbi_load(filename, &width, &height, &bPerPix, 0);

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);

	return tex;
}

/*
void SetTexture(int idx, char *fname) {
	
	if (myTex) delete[] myTex;
	glBindTexture(GL_TEXTURE_2D, tex[idx]);
	myTex = stbi_load(fname, &texWidth, &texHeight, &bitPerPixel, 0);
	glActiveTexture(GL_TEXTURE0+idx);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myTex);
	delete[] myTex; myTex = NULL;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, tex[idx]);
	glEnable(GL_TEXTURE_2D);
}*/
	
void drawQuad(void) {
	glBegin(GL_QUADS);
	glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
	glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
	glVertex3f(-1, 1, 0);
	glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
	glMultiTexCoord2f(GL_TEXTURE1, 0, 2);
	glVertex3f(-1, -1, 0);
	glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
	glMultiTexCoord2f(GL_TEXTURE1, 2, 2);
	glVertex3f(1, -1, 0);
	glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
	glMultiTexCoord2f(GL_TEXTURE1, 2, 0);
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

	glBindTexture(GL_TEXTURE_2D, tex[0]);
	drawQuad();
	
	glutSwapBuffers();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	// stage 0
	glActiveTexture(GL_TEXTURE0);
	tex[0] = LoadTexture("dirty.jpg");

	// stage 1
	glActiveTexture(GL_TEXTURE1);
	tex[1] = LoadTexture("robot.jpg");
	
	
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("My Texture");

	glewInit();
	init();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);

	glutMainLoop();

	return 0;
}
