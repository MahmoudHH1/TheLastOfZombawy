#pragma once
#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:

	float posX, posY, posZ;  // position components in a linear fashion
	float rotX, rotY, rotZ;  // rotation components in a linear fashion

	Bullet(float x, float y, float z, float rotX, float rotY, float rotZ);
	Bullet();

	void Draw();
	void update(float deltaTime);
};

#endif // !BULLET_H