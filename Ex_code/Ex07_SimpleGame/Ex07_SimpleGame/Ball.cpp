#include "Ball.h"
#include "OpenGLHeaders.h"
#include "myPannel.h"
#include <math.h>

Vector3f ballPosition;
Vector3f ballVelocity;

#define RAD 0.1

void BallSet(float x, float y, float z, float vx, float vy, float vz) {
	ballPosition.x = x;
	ballPosition.y = y;
	ballPosition.z = z;
	ballVelocity.x = vx;
	ballVelocity.y = vy;
	ballVelocity.z = vz;
}

void BallMove(void) {
	// v = dx/dt;
	// dx = v*dt;
	// dx = 현재위치 - 이전위치
	ballPosition.x = ballPosition.x + ballVelocity.x * 0.01;
	ballPosition.y = ballPosition.y + ballVelocity.y * 0.01;
	ballPosition.z = ballPosition.z + ballVelocity.z * 0.01;

	if (ballPosition.x + RAD > 1.0 || ballPosition.x - RAD < -1.0) {
		ballVelocity.x *= -1.0; 
	}
	if (ballPosition.y + RAD > 1.0 || ballPosition.y - RAD < -1.0) {
		ballVelocity.y *= -1.0; 
	}
	if (ballPosition.z - RAD < -1.0) {
		ballVelocity.z *= -1.0; 
	}

	// pannel collision
	float pannelX = GetPannelX();
	float pannelY = GetPannelY();
	if (ballPosition.z + RAD > 1.0) {
		float dx = pannelX - ballPosition.x;
		float dy = pannelY - ballPosition.y;
		float dist = sqrt(dx*dx + dy*dy);
		if (dist < 0.6) ballVelocity.z *= -1.0;
		else exit(1);
	}

}

void BallDraw(void) {
	glPushMatrix();
	glTranslatef(ballPosition.x, ballPosition.y, ballPosition.z);
	glutSolidSphere(0.1, 30, 30);
	glPopMatrix();

}
