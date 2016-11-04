#include "Light.h"

void SetMaterial(float r, float g, float b) {
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
}

void SetLight(float r, float g, float b) {
	GLfloat diffuse[] = { r, g, b, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	
}

void SetLightPosition(float pos[]) {
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

}