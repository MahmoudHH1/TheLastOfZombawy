#ifndef COIN_H
#define COIN_H

#include "Model_3DS.h"

class Coin :public Model_3DS {
public:
	Coin();
	Coin(float x, float y, float z, float rotX, float rotY, float rotZ);
};

#endif