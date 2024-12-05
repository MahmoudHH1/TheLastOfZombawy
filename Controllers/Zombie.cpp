#include "Headers/Zombie.h"
#include "Headers/Model_3DS.h"

#include <math.h>
#include <glut.h>

#define M_PI 3.14159265358979323846

Zombie::Zombie(float x, float y, float z,
	float rotX, float rotY, float rotZ, float scale ,int hitDamage) :
	Model_3DS(x, y, z, rotX, rotY, rotZ ,scale ), health(100), hitDamage(hitDamage) {
	Load("Assets/Models/Zombie/Zombie.3ds");
};

Zombie::Zombie() :
	Model_3DS(0, 0, 0, 0, 0, 0,0.1f), health(100), hitDamage(50) {
	Load("Assets/Models/Zombie/Zombie.3ds");
};

void Zombie::moveBackwards(float distance) {
    // Convert yaw (rot.y) to radians if it's in degrees
    float radYaw = rot.y * (M_PI / 180.0f);

    // Calculate the movement vector based on the rotation
    // Moving backwards means moving in the opposite direction of the yaw
    float moveX = sin(radYaw) * distance;
    float moveZ = cos(radYaw) * distance;

    // Update the position
    pos.x -= moveX;
    pos.z -= moveZ;
}
