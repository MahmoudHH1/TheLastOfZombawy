#pragma once
#ifndef BIG_ZOMBIE_H
#define BIG_ZOMBIE_H

#include "Zombie.h"
#include "Model_3DS.h"

class BigZombie : public Model_3DS {
public:
	int hitDamage;
	int health;

	BigZombie(float x, float y, float z,
		float rotX, float rotY, float rotZ, float scale, int hitDamage);
	BigZombie();
};

#endif // !BIG_ZOMBIE_H
