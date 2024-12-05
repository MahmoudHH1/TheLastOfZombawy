#include "Headers/BigZombie.h"
#include "Headers/Model_3DS.h"

BigZombie::BigZombie(float x, float y, float z, float rotX, float rotY, float rotZ, float scale, int hitDamage) :
	Model_3DS(x, y, z, rotX, rotY, rotZ, scale), health(100), hitDamage(hitDamage) {
	Load("Assets/models/zombie/BigZombie.3ds");
};

BigZombie::BigZombie() :Model_3DS(0, 0, 0, 0, 0, 0, 0), health(100), hitDamage(20) {
	Load("Assets/models/zombie/BigZombie.3ds");
};