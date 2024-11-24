#ifndef SHOOTER_H 
#define SHOOTER_H 

#include "Model_3DS"

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

	Shooter(float x, float y, float z
		, float rotX, float rotY, float rotZ);
	Shooter();
	void CollectKey();
	void CollectMedKit();
	void heal();

}

#endif SHOOTER_H