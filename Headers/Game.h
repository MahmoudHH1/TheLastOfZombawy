#ifndef GAMAE_H
#define GAME_H

#include "Shooter.h"
#include "Zombie.h"
#include "Camera.h"
#include "Coin.h"
#include "Key.h"
#include "MedKit.h"
#include "Bullet.h"
#include "BigZombie.h"
#include <vector>
class Game {
	public :
		Shooter shooter;
		Cam camera;
		int level;
		bool isDoorOpen;
		bool isGameWon;
		bool isGameOver;
		BigZombie bigZombie;
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
		void updateBigZombie();
		void updateCamera();
		void updateFlashlight();
		void spawnZombies();
		void spawnKey();
		void spawnMedkit();
		void shootBullet();
		void handleKeyPress(unsigned char key , int x , int y);
		void handleOpenDoor(Shooter shooter);
		void calculateDeltaTime();
};

#endif // !GAMAE_H