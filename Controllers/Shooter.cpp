#include <stdio.h>
#include <iostream>
#include "Headers/Shooter.h"
#include "Headers/Model_3DS.h"

using namespace std;

Shooter::Shooter(float x, float y, float z,
	float rotX, float rotY, float rotZ, float scale) :
	health(100), score(0), hitDamage(50)
	, Model_3DS(x, y, z, rotX, rotY, rotZ, scale), hasKey(false), medkits(0) {
	Load("Assets/models/Shooter/Shooter.3DS");
};

Shooter::Shooter() :
	health(100), score(0), hitDamage(50),
	Model_3DS(3, 0, -27, 0, 0, 0, 0.1), hasKey(false), medkits(0) {
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

void Shooter::moveForward() {
	//if (pos.z <= 18.2) 
		pos.z += speed;
}
void Shooter::moveBackward() {
	//if (pos.z >= 5.1) 
		pos.z -= speed;
	
}
void Shooter::moveLeft() {
	//if (pos.x <= 18.1)
		pos.x += speed;
}
void Shooter::moveRight() {
	//if (pos.x >= -18.5)
		pos.x -= speed;
}