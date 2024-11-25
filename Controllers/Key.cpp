#include "../Headers/Key.h"
#include "../Headers/Model_3DS.h"
#include <glut.h>

Key::Key() : Model_3DS(0, 0, 0, 0, 0, 0) {
	//Load("../Assets/models/Key/Key.3ds");
}

Key::Key(float x, float y, float z, float rotX, float rotY, float rotZ) : Model_3DS(x, y, z, rotX, rotY, rotZ) {
	//Load("../Assets/models/Key/Key.3ds");
}


