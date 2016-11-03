#include "enemyPannel.h"
#include "OpenGLHeaders.h"

float enemyX = 0;
float enemyY = 0;

float GetEnemyX(void) { return enemyX; }
float GetEnemyY(void) { return enemyY; }

void EnemyMove(float dx, float dy) {
	enemyX += dx;
	enemyY += dy;

}

void EnemyDraw(void) {

	glPushMatrix();
	glTranslatef(enemyX, enemyY, -1.0);
	glScalef(0.5, 0.5, 0.01);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

}