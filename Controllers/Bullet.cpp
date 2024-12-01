#include <Headers/Bullet.h>
#include <cmath>
#include <glut.h>
#include <iostream>
#define speed 0.5

Bullet::Bullet(float x, float y, float z, float rotX, float rotY, float rotZ)
	: posX(x), posY(y), posZ(z), rotX(rotX), rotY(rotY), rotZ(rotZ) {}

Bullet::Bullet() : posX(0), posY(0), posZ(0), rotX(0), rotY(0), rotZ(0) {}

void Bullet::update(float deltaTime) {

	// Calculate the direction based on rotation (assuming simple 3D space)
	float dirX = cos(rotY) * cos(rotX);  // Yaw * Pitch
	float dirY = sin(rotX);                     // Pitch
	float dirZ = sin(rotY) * cos(rotX);  // Yaw * Pitch

	// Update position based on direction and speed
	posX += dirX * speed * deltaTime;
	posY += dirY * speed * deltaTime;
	posZ += dirZ * speed * deltaTime;
}

void Bullet::Draw() {
    glPushMatrix();
	std::cout << posX << posY << posZ<<std::endl;
	//glTranslatef(posX, posY, posZ);
	glutSolidCube(30);

	glPopMatrix();
}