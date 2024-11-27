#include <stdio.h>
#include <iostream>
#include <cctype>
#include "Headers/Game.h"
#include "Headers/Zombie.h"
#include "Headers/Coin.h"
#include "Headers/Key.h"
#include "Headers/MedKit.h"
#include "Headers/Camera.h"
#include "Headers/RenderEnviroment.h"

#include <vector>

bool isMouseLocked = true;
float camMoveSpeed = 0.2f; // Camera movement speed


using namespace std;

Game::Game() {
    loadEnvironmentAssets();
    zombies.push_back(Zombie(10.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.1f, 12));
    keys.push_back(Key(16.5f, 0.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.7f)); // X = 16.5 , Z = 17
    coins.push_back(Coin(2.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.1f));
    //medkits.push_back(Medkit(8.0f, 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.01f, 12));
    camera = Cam();
    updateCamera();
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
	if (keys.size() > 0 && shooter.CollidesWithOffset(keys[0], 1.5f, 1.5f)) {
        std::cout << "Collected" << endl;
        shooter.CollectKey();
        keys.clear();
    }
}

void Game::updateCamera() {


    // Player position
    Vector3f playerPos = { shooter.pos.x , shooter.pos.y , shooter.pos.z };
    Vector3f cameraOffset;
    Vector3f forwardOffset;
    if (camera.isThirdPerson) {
        // Offset to place the camera slightly behind and above the player's right shoulder
        cameraOffset = Vector3f(1.75f, 8.5f, -5.0f);
        forwardOffset = Vector3f(0.0f, 5.5f, 3.0f);
        // Keep the camera upright
        camera.top = Vector3f(0.0f, 1.0f, 0.0f);
    }
    else { // first Person
		// Offset to place the camera slightly above the player's head
		cameraOffset = Vector3f(0.0f, 7.5f, 0.0f);
		forwardOffset = Vector3f(0.0f, 7.0f, 1.5f);
		// Keep the camera upright
		//camera.top = Vector3f(0.0f, 5.0f, 0.0f);
    }
    // Set camera position relative to the player's position
    camera.eye = playerPos + cameraOffset;
    camera.center = playerPos + forwardOffset;
}

void Game::handleKeyPress(unsigned char key, int x, int y) {
    key = std::tolower(key);
    switch (key) {
    case 'w':
        shooter.moveForward();
        updateCamera();
        break;
    case 's':
        shooter.moveBackward();
        updateCamera();
        break;
    case 'a':
        shooter.moveLeft();
        updateCamera();
        break;
    case 'd':
        shooter.moveRight();
        updateCamera();
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
    case 'p':
		camera.toggleThirdPerson();
		updateCamera();
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
