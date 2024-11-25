#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Model_3DS.h"

class Zombie : public Model_3DS {
public:
	int health;
	int hitDamage;


	Zombie(float x, float y, float z,
		float rotX, float rotY, float rotZ,
		float scale, int hitDamage);
	Zombie();

	void getHit(int hitDamage);

};


#endif // !ZOMBIE_H

