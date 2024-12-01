#ifndef GAMAE_H
#define GAME_H

#include "Shooter.h"
#include "Zombie.h"
#include "Camera.h"
#include "Coin.h"
#include "Key.h"
#include "MedKit.h"
#include "Bullet.h"
#include <vector>
class Game {
	public :
		Shooter shooter;
		Cam camera;
		std::vector<Zombie> zombies;
		std::vector<Coin> coins;
		std::vector<Key> keys;
		std::vector<Medkit> medkits;
		std::vector<Bullet> bullets;

		Game();
		void Draw();
		void drawHUD();
		void update();
		void updateZombies();
		void updateCamera();
		void updateFlashlight();
		void spawnZombies();
		void spawnKey();
		void spawnMedkit();
		void handleKeyPress(unsigned char key , int x , int y);
		void calculateDeltaTime();
};

#endif // !GAMAE_H