#include "Headers/Coin.h"

Coin::Coin() : Model_3DS(0, 0, 0, 0, 0, 0 , 0.1f) {
	Load("Assets/models/Coin/Coin.3ds");
}

Coin::Coin(float x, float y, float z, float rotX, float rotY, float rotZ , float scale) : Model_3DS(x, y, z, rotX, rotY, rotZ , scale) {
	Load("Assets/models/Coin/Coin.3ds");
}