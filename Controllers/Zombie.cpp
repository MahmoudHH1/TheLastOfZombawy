#include "../Headers/Zombie.h"
#include "../Headers/Model_3DS.h"
#include <glut.h>

Zombie::Zombie(float x, float y, float z,
	float rotX, float rotY, float rotZ, int hitDamage) :
	Model_3DS(x, y, z, rotX, rotY, rotZ), health(100), hitDamage(hitDamage) {
	//Load("../Assets/Models/Zombie/Zombie.3ds");
};

Zombie::Zombie() :
	Model_3DS(0, 0, 0, 0, 0, 0), health(100), hitDamage(50) {
	//Load("../Assets/Models/Zombie/Zombie.3ds");
};

void Zombie::getHit(int hitDamage) {
	if (hitDamage > health)
		health = 0;
	else
		health -= hitDamage;
}
