#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Headers/Shooter.h"
#include "Headers/Model_3DS.h"

using namespace std;

#define speed 0.5
#define M_PI 3.14159265358979323846

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

bool Shooter::isCollidingWithMiddleWall(float newX ,float newZ) {
    return (((newX>= -32 && newX < -1.5) || (newX <= 32 && newX > 2)) && newZ >= 2 && newZ<= 6.5);
}

bool Shooter::inBounds(float newX , float newZ) {
    return (newZ >= -32 && newZ <= 32 && newX >= -32 && newX <= 32);
}

bool Shooter::isCollidingWithDoor(float newX,float newZ) {
	return (newX >= -1.5 && newX <= 2 && newZ >= 2 && newZ <= 6.5);
}


void Shooter::moveForward(int level , bool isDoorOpen) {
    float yawRad = rot.y * M_PI / 180.0f; // Convert yaw rotation to radians
    float newZ = pos.z + speed * cosf(yawRad); // Forward movement along z-axis
    float newX = pos.x + speed * sinf(yawRad); // Forward movement along x-axis

    // Check boundary conditions before updating position
    if (!isCollidingWithMiddleWall(newX , newZ)&& inBounds(newX , newZ) &&(!isCollidingWithDoor(newX , newZ)|| (level==2 && isDoorOpen) ))
    {
        pos.z = newZ;
        pos.x = newX;
    }
    /*if (newZ >= -32 && newZ <= 32 && newX >= -32 && newX <= 32) {
        
    }*/
}

void Shooter::moveBackward(int level , bool isDoorOpen) {
    float yawRad = rot.y * M_PI / 180.0f; // Convert yaw rotation to radians
    float newZ = pos.z - speed * cosf(yawRad); // Backward movement along z-axis
    float newX = pos.x - speed * sinf(yawRad); // Backward movement along x-axis

    // Check boundary conditions before updating position
    if (!isCollidingWithMiddleWall(newX, newZ) && inBounds(newX, newZ) && (!isCollidingWithDoor(newX, newZ) || (level == 2 && isDoorOpen)))
    {
        pos.z = newZ;
        pos.x = newX;
    }
}

void Shooter::moveLeft(int level, bool isDoorOpen) {
    float yawRad = rot.y * M_PI / 180.0f; // Convert yaw rotation to radians
    float newZ = pos.z - speed * sinf(yawRad); // Left movement along z-axis
    float newX = pos.x + speed * cosf(yawRad); // Left movement along x-axis

    // Check boundary conditions before updating position
    if (!isCollidingWithMiddleWall(newX, newZ) && inBounds(newX, newZ) && (!isCollidingWithDoor(newX, newZ) || (level == 2 && isDoorOpen)))
    {
        pos.z = newZ;
        pos.x = newX;
    }
}

void Shooter::moveRight(int level, bool isDoorOpen) {
    float yawRad = rot.y * M_PI / 180.0f; // Convert yaw rotation to radians
    float newZ = pos.z + speed * sinf(yawRad); // Right movement along z-axis
    float newX = pos.x - speed * cosf(yawRad); // Right movement along x-axis

    // Check boundary conditions before updating position
    if (!isCollidingWithMiddleWall(newX, newZ) && inBounds(newX, newZ) && (!isCollidingWithDoor(newX, newZ) || (level == 2 && isDoorOpen)))
    {
        pos.z = newZ;
        pos.x = newX;
    }
}
