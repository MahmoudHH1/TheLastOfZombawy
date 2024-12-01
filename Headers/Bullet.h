#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Model_3DS.h"

class Bullet : public Model_3DS {
public:
	bool isActive = true;

	Bullet(float x, float y, float z, float rotX, float rotY, float rotZ , float scale);
	Bullet();

	void Draw();
	void update();
};

#endif // !BULLET_H