#include "Headers/Shooter.h"
#include "Headers/Model_3DS.h"

Shooter::Shooter(float x, float y, float z,
	float rotX, float rotY, float rotZ , float scale) :
	health(100), score(0), hitDamage(50)
	, Model_3DS(x, y, z, rotX, rotY, rotZ , scale) , hasKey(false) , medkits(0) {
	Load("Assets/models/Shooter/Shooter.3DS");
};

Shooter::Shooter() :
	health(100), score(0), hitDamage(50),
	Model_3DS(0, 0, 0, 0, 0, 0 , 0.1) , hasKey(false) , medkits(0) {
	Load("Assets/models/Shooter/Shooter.3DS");
};

void Shooter::CollectKey() {
	hasKey = true;
}

void Shooter::CollectCoin() {
	score += 10;
}

void Shooter::CollectMedKit() {
	++medkits;
}

void Shooter::Heal(int healthRecovery) {
	if (healthRecovery + health > 100) {
		health = 100;
	}
	else {
		health += healthRecovery;
	}
}

