#ifndef MEDKIT_H
#define MEDKIT_H

#include "Model_3DS.h"

class Medkit : public Model_3DS {
public:
	int healthRecovery;
	Medkit(float x, float y, float z,
		float rotX, float rotY, float rotZ , 
		int healthRecovery);
	Medkit();

	void spawnMidkets(int groundLenght , int groundWidth);
};

#endif MEDKIT_H