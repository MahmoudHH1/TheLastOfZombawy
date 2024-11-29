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
    spawnZombies();
    spawnMedkit();
    coins.push_back(Coin(2.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.1f));
    camera = Cam();
    updateCamera();

    for (int i = 0; i < medkits.size(); i++)
    {
        cout << "med " << i << " x " << medkits[i].pos.x <<" Z " << medkits[i].pos.z << endl;
    }
}



// Add this implementation to your Game.cpp
void renderText(float x, float y, const char* text) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f); // White text
    glRasterPos2f(x, y);

    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void Game::drawHUD() {
    char buffer[200];

    // Display Score
    sprintf(buffer, "Score: %d", shooter.score);
    renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 20, buffer);

    // Display Coordinates
    sprintf(buffer, "Position: (%.2f, %.2f, %.2f)",
        shooter.pos.x, shooter.pos.y, shooter.pos.z);
    renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 40, buffer);

	//Display the number of medkits collected
	sprintf(buffer, "Medkits: %d", shooter.medkits);
	renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 60, buffer);

	// Display Health
	sprintf(buffer, "Health: %d", shooter.health);
	renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 80, buffer);

	// Display Key
	if (shooter.hasKey) {
		renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 100, "Key: Collected");
	}
	else {
		renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 100, "Key: Not Collected");
	}


}


void Game::Draw() {
    RenderEnvironment();
    drawHUD();

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
	for (int i = 0; i <= 50; i+=10) {
		zombies.push_back(Zombie(10.0f+i, 4.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.07f, 12));
	}
}

void Game::spawnKey() {
    keys.push_back(Key(16.5f, 0.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.7f)); // X = 16.5 , Z = 17
}

void Game::spawnMedkit() {
    medkits.push_back(Medkit(23.0f,0.0f,23.0f,0.0f,0.0f,0.0f,0.01f,10));
    medkits.push_back(Medkit(23.0f, 0.0f, -23.0f, 0.0f, 0.0f, 0.0f, 0.01f, 10));
    medkits.push_back(Medkit(-23.0f, 0.0f, 23.0f, 0.0f, 0.0f, 0.1f, 0.01f, 10));
    medkits.push_back(Medkit(-23.0f, 0.0f, -23.0f, 0.0f, 0.0f, 0.1f, 0.01f, 10));
}

void Game::update() {
	if (keys.size() > 0 && shooter.CollidesWith(keys[0])) {
        std::cout << "Collected" << endl;
        shooter.CollectKey();
        keys.clear();
    }
    for (int i = 0; i < medkits.size(); i++) {
        if (shooter.CollidesWithOffset(medkits[i] ,1.0f , 1.0f)) {
            std::cout << "collesion with med" << endl;
            shooter.CollectMedKit();
            medkits.erase(medkits.begin() + i);
        }
    }

    for (int i = 0; i < coins.size(); i++)
    {
        if (shooter.CollidesWith(coins[i])) {
            shooter.CollectCoin();
			coins.erase(coins.begin() + i);
        }
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
