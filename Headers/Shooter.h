#ifndef SHOOTER_H 
#define SHOOTER_H 

#include "Model_3DS.h"

class Shooter : public Model_3DS {
public:
	//init with positions and rotation angles 
	//has score 
	//
	int health;
	int score;
	int hitDamage;
	int medkits;
	bool hasKey;

	#define speed 0.3f;

	Shooter(float x, float y, float z
		, float rotX, float rotY, float rotZ, float scale);
	Shooter();
	void CollectKey();
	void CollectCoin();
	void CollectMedKit();
	void Heal(int healthRecovery);
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
};

#endif SHOOTER_H