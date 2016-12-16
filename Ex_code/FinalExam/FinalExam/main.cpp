#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/glut.h>

#include <math.h>
#include "STBImage.h"
#include "mesh.h"

#define NTEXTURES 2

float arm1XAngle = 0;
float arm2ZAngle = 0;

GLuint tex[NTEXTURES];
GLuint clothTex;

unsigned char *myTex=NULL;
int texWidth, texHeight, bitPerPixel;

CMesh mesh1, mesh2;

//light parameters
GLfloat lit_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lit_specular[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lit_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lit_position0[] = { 0, 5, 0, 1 };
GLfloat lit_position1[] = { 0, 5, 5, 1 };


// material parameters
GLfloat mat_diffuse[] = { 1.0, 1.0, 0.3, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[] = { 0.0, 0.03, 0.0, 1.0 };

void SetLighting(void) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lit_ambient);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lit_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lit_diffuse);


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 90);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lit_specular);
}

void SetLightPosition(void) {
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, lit_position1);
}

void keyboard(unsigned char c, int, int) {
	switch (c) {
	case 27: exit(0);
	case 'w': arm1XAngle -= 1; break;
	case 's': arm1XAngle += 1; break;
	case 'a': arm2ZAngle += 1; break;
	case 'd': arm2ZAngle -= 1; break;
	case 'j': lit_position0[0] -= 0.1; lit_position1[0] -= 0.1; break;
	case 'k': lit_position0[0] += 0.1; lit_position1[0] += 0.1; break;
	}
}

void PrepareTextures(int n, GLuint *textures) {
	glGenTextures(n, tex);
	glGenTextures(1, &clothTex);

	if (myTex) delete[] myTex;
	glBindTexture(GL_TEXTURE_2D, clothTex);
	myTex = stbi_load("clothTex.jpg", &texWidth, &texHeight, &bitPerPixel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myTex);
	delete[] myTex; myTex = NULL;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
	glEnable(GL_TEXTURE_2D);
}
	
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
	gluLookAt(6,5,8, 0, 5, 0, 0, 1, 0);
	SetLightPosition();

	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glScalef(2, 0.5, 2);
	glutSolidCube(1.0);
	glPopMatrix();

	glTranslatef(0,0.25,0);
	glutSolidSphere(0.3, 30, 30);

	
	glRotatef(arm1XAngle, 1, 0, 0);
	glTranslatef(0.0, 0.5, 0.0);
		glPushMatrix();
		glScalef(0.2, 1.0, 0.2);
		glutSolidCube(1.0);
		glPopMatrix();
	glTranslatef(0.0, 0.5, 0.0);
	glutSolidSphere(0.3, 30, 30);

	glRotatef(arm2ZAngle, 0, 0, 1);
	glTranslatef(0.0, 0.5, 0.0);
	glPushMatrix();
	glScalef(0.2, 1.0, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();

	glTranslatef(0, 0.5, 0);
	glPushMatrix();
	glScalef(2, 0.1, 2);
	glutSolidCube(1.0);
	glPopMatrix();




	// 자동 텍스처 생성
	glActiveTexture(GL_TEXTURE0);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(0.1, 0.1, 0.1);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glEnable(GL_TEXTURE_GEN_S); glEnable(GL_TEXTURE_GEN_T);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glMatrixMode(GL_MODELVIEW);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_GEN_S); glEnable(GL_TEXTURE_GEN_T);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glActiveTexture(GL_TEXTURE0);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(0.1, 0.1, 0.1);
	glBindTexture(GL_TEXTURE_2D, clothTex);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	mesh2.show();

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	mesh1.show();
	
	glPopMatrix();





	
	glutSwapBuffers();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	PrepareTextures(NTEXTURES, tex);
	// stage 0
	glActiveTexture(GL_TEXTURE0);
	SetTexture(0, "dirty.jpg");

	// stage 1
	glActiveTexture(GL_TEXTURE1);
	SetTexture(1, "spheremap.jpg");
	
	mesh1.read("complex.sms");
	mesh2.read("cloth.sms");

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	SetLighting();
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
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
