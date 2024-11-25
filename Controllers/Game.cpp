#include "Headers/Game.h"
#include "Headers/Zombie.h"
#include "Headers/Coin.h"
#include "Headers/Key.h"
#include "Headers/MedKit.h"
#include "Headers/RenderEnviroment.h"

#include <vector>


Game::Game() {
	loadEnvironmentAssets();
	zombies.push_back(Zombie(10.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f , 0.1f ,  12));
	keys.push_back(Key(5.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f , 1.0f));
	coins.push_back(Coin(2.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f , 0.1f));
	medkits.push_back(Medkit(8.0f, 0.0f, 8.0f, 0.0f, 0.0f, 0.0f , 0.01f,12));
}

void Game::Draw() {
	RenderEnvironment();
	shooter.Draw();
	for (int i = 0; i < zombies.size(); i++) {
		zombies[i].Draw();
	}
	for (int i = 0; i < coins.size(); i++) {
		coins[i].Draw();
	}
	for (int i = 0; i < keys.size(); i++) {
		keys[i].Draw();
	}
	for (int i = 0; i < medkits.size(); i++) {
		medkits[i].Draw();
	}
}

void Game::spawnZombies() {
	//zombies.push_back(Zombie());
}

void Game::spawnKey() {
	//keys.push_back(Key());
}

void Game::spawnMedkit() {
	//medkits.push_back(Medkit());
}

void Game::update() {

}