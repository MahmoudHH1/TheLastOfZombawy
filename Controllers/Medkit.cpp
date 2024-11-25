#include "Headers/Medkit.h"
#include "Headers/Model_3DS.h"

Medkit::Medkit(float x, float y, float z,
	float rotX, float rotY, float rotZ, float scale, int healthRecovery) :
	healthRecovery(healthRecovery), Model_3DS(x, y, z, rotX, rotY, rotZ, scale) {
	Load("Assets/models/Medkit/Medkit.3ds");
};

Medkit::Medkit() :healthRecovery(100), Model_3DS(0, 0, 0, 0, 0, 0, 0.1f) {
	Load("Assets/models/Medkit/Medkit.3ds");
};
