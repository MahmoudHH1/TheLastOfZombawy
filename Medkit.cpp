#include "Medkit.h"
#include "Model_3DS"

Medkit::Medkit(float x, float y, float z,
	float rotX, float rotY, float rotZ, int healthRecovery) :
	healthRecovery(healthRecovery), Model_3DS(x, y, z, rotX, rotY, rotZ) {};

Medkit::Medkit() :healthRecovery(100), Model_3DS(0, 0, 0, 0, 0, 0) {};

//to be implemented after drawing the ground and the scene
void spawnMidkets(int groundLength, int groundWidth) {
	
}