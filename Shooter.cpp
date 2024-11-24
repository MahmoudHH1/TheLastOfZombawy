#include "Shooter.h"
#include "Model_3DS.h"

Shooter::Shooter(float x, float y, float z,
	float rotX, float rotY, float rotZ) :
	health(100), score(0), hitDamage(50)
	, Model_3DS(x, y, z, rotX, rotY, rotZ) {};

Shooter::Shooter() :
	health(100), score(0), hitDamage(50),
	Model_3DS(0, 0, 0, 0, 0, 0) {};

void Shooter::CollectKey() {
	hasKey = true;
}

void Shooter::CollectCoint() {
	score += 10;
}

void Shooter::CollectMedKit() {
	++medkits;
}

void Shooter::heal(int healthRecovery) {
	if (healthRecovery + health > 100) {
		health = 100;
	}
	else {
		health += healthRecovery;
	}
}

