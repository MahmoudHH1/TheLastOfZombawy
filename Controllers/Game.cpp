#include "Headers/Game.h"
#include "Headers/Zombie.h"
#include "Headers/Coin.h"
#include "Headers/Key.h"
#include "Headers/MedKit.h"
#include "Headers/Camera.h"
#include "Headers/RenderEnviroment.h"

#include <vector>

bool isMouseLocked = true;
float camMoveSpeed = 0.05f; // Camera movement speed


Game::Game() {
	loadEnvironmentAssets();
    camera = Cam();
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

void Game::handleKeyPress(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        camera.moveForward(camMoveSpeed);
        break;
    case 's':
        camera.moveForward(-camMoveSpeed);
        break;
    case 'a':
        camera.moveRight(-camMoveSpeed);
        break;
    case 'd':
        camera.moveRight(camMoveSpeed);
        break;
    case ' ':
        camera.moveUp(camMoveSpeed);
        break;
    case 'c':
        camera.moveUp(-camMoveSpeed);
        break;
    case 't':
        camera.eye = Vector3f(0, 5, 0);
        camera.center = Vector3f(0, 0, 0);
        camera.top = Vector3f(0, 0, -1);
        break;
    case 'y':
        camera.eye = Vector3f(5, 0, 0);
        camera.center = Vector3f(0, 0, 0);
        camera.top = Vector3f(0, 1, 0);
        break;
    case 'u':
        camera.eye = Vector3f(0, 0, 5);
        camera.center = Vector3f(0, 0, 0);
        camera.top = Vector3f(0, 1, 0);
        break;
    case 27: // Escape key
        isMouseLocked = false;
        exit(EXIT_SUCCESS);
        break;
    default:
        // Handle other keys or do nothing
        break;
    }
}
