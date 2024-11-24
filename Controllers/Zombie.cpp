#include "../Headers/Zombie.h"
#include "../Headers/Model_3DS.h"

Zombie::Zombie(float x, float y, float z,
	float rotX, float rotY, float rotZ, int hitDamage) :
	Model_3DS(x, y, z, rotX, rotY, rotZ), health(100), hitDamage(hitDamage) {};

Zombie::Zombie() :
	Model_3DS(0, 0, 0, 0, 0, 0), health(100), hitDamage(50) {};

void Zombie::getHit(int hitDamage) {
	if (hitDamage > health)
		health = 0;
	else
		health -= hitDamage;
}