#ifndef GAMAE_H
#define GAME_H

#include "Shooter.h"
#include "Zombie.h"
#include "Camera.h"
#include "Coin.h"
#include "Key.h"
#include "MedKit.h"
#include <vector>

class Game {
	public :
		Shooter shooter;
		Cam camera;
		std::vector<Zombie> zombies;
		std::vector<Coin> coins;
		std::vector<Key> keys;
		std::vector<Medkit> medkits;

		Game();
		void Draw();
		void update();
		void updateZombies();
		void spawnZombies();
		void spawnKey();
		void spawnMedkit();
		void handleKeyPress(unsigned char key , int x , int y);
		void updateCamera();
		void drawHUD();
		void calculateDeltaTime();
};

#endif // !GAMAE_H