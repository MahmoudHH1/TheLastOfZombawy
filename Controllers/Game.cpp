#include <stdio.h>
#include <iostream>
#include <cctype>
#include "Headers/Game.h"
#include "Headers/Zombie.h"
#include "Headers/Coin.h"
#include "Headers/Key.h"
#include "Headers/Bullet.h"
#include "Headers/MedKit.h"
#include "Headers/Camera.h"
#include "Headers/RenderEnviroment.h"

#include<chrono>
#include <vector>

bool isMouseLocked = true;
bool isFlashlightOn = true;
float camMoveSpeed = 0.2f; // Camera movement speed
float collisionTimer = 0.0f; // Timer to track elapsed time
float deltaTime = 0.0f;      // Time elapsed per frame
std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;

#define M_PI 3.14159265358979323846
#define FLASHLIGHT_LIGHT GL_LIGHT2  // Using LIGHT2 for the flashlight

using namespace std;

Game::Game() {
	loadEnvironmentAssets();
	spawnZombies();
	spawnMedkit();
	spawnKey();
	coins.push_back(Coin(2.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.1f));
	camera = Cam();
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

	// Display Coordinates
	sprintf(buffer, "Rotation angles: (%.2f, %.2f, %.2f)",
		shooter.rot.x, shooter.rot.y, shooter.rot.z);
	renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 60, buffer);

	//Display the number of medkits collected
	sprintf(buffer, "Medkits: %d", shooter.medkits);
	renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 80, buffer);

	// Display Health
	sprintf(buffer, "Health: %d", shooter.health);
	renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 100, buffer);

	// Display Key
	if (shooter.hasKey) {
		renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 120, "Key: Collected");
	}
	else {
		renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 120, "Key: Not Collected");
	}


}


void Game::Draw() {
	RenderEnvironment();
	drawHUD();

	shooter.Draw();
	for (int i = 0; i < zombies.size(); i++) {
		if (zombies[i].health > 0) {
			zombies[i].Draw();
		}
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
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isActive) {
			bullets[i].Draw();
		}
	}
}


void Game::spawnZombies() {
	for (int i = 0; i < 50; i += 10) {
		zombies.push_back(Zombie(-20 + i, 4.0f, -1.0f, 0.0f, 180.0f, 0.0f, 0.07f, 12));
	}
}

void Game::spawnKey() {
	keys.push_back(Key(28.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.7f));
}

void Game::spawnMedkit() {
	medkits.push_back(Medkit(23.0f, 0.0f, 23.0f, 0.0f, 0.0f, 0.0f, 0.01f, 10));
	medkits.push_back(Medkit(23.0f, 0.0f, -23.0f, 0.0f, 0.0f, 0.0f, 0.01f, 10));
	medkits.push_back(Medkit(-23.0f, 0.0f, 23.0f, 0.0f, 0.0f, 0.1f, 0.01f, 10));
	medkits.push_back(Medkit(-23.0f, 0.0f, -23.0f, 0.0f, 0.0f, 0.1f, 0.01f, 10));
}


void Game::shootBullet() {
	bullets.push_back(Bullet(shooter.pos.x, shooter.pos.y + 4, shooter.pos.z, shooter.rot.x, shooter.rot.y, shooter.rot.z, 0.1f));
}

void Game::update() {
	collisionTimer += deltaTime;

	if (keys.size() > 0 && shooter.CalculateCollisionWithLocation(keys[0], 1.7f, 1.7f)) {
		shooter.CollectKey();
		keys.clear();
	}
	for (int i = 0; i < medkits.size(); i++) {
		if (shooter.CalculateCollisionWithLocation(medkits[i], 1.0f, 1.0f)) {
			shooter.CollectMedKit();
			medkits.erase(medkits.begin() + i);
		}
	}

	for (int i = 0; i < coins.size(); i++)
	{
		if (shooter.CalculateCollisionWithLocation(coins[i], 1.5f, 1.5f)) {
			shooter.CollectCoin();
			coins.erase(coins.begin() + i);
		}
	}


	if (collisionTimer >= 1.0f) {
		// Check for collision with zombies
		for (int i = 0; i < zombies.size(); i++) {
			if (shooter.CalculateCollisionWithLocation(zombies[i], 3.0f, 3.0f)) {
				shooter.health -= zombies[i].hitDamage; // Reduce health on collision
			}
		}
		// Reset the timer after checking
		collisionTimer = 0.0f;
	}

	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isActive)
		{
			bullets[i].update();
			for (int j = 0; j < zombies.size(); j++)
			{
				if (zombies[j].health > 0 && zombies[j].CalculateCollisionWithLocation(bullets[i], 1.0f, 1.0f)) {
					zombies[j].health -= shooter.hitDamage;
					zombies[j].moveBackwards(2.0f);
					bullets[i].isActive = false;
					if (zombies[j].health <= 0)
					{
						coins.push_back(Coin(zombies[j].pos.x, 0.0f, zombies[j].pos.z, 0.0f, 0.0f, 0.0f, 0.1f));
					}
				}
			}
		}

	}

	calculateDeltaTime();
	updateZombies();
	updateFlashlight();
	updateCamera();
}

void Game::updateFlashlight() {
	if (!isFlashlightOn) {
		glDisable(FLASHLIGHT_LIGHT);
		return;
	}

	glEnable(FLASHLIGHT_LIGHT);

	// Calculate flashlight position with adjusted offsets
	float flashlightOffsetY = 7.0f;
	float flashlightOffsetZ = 2.0f;  // Increased forward offset

	// Position the flashlight
	GLfloat light_position[] = {
		shooter.pos.x,
		shooter.pos.y + flashlightOffsetY,
		shooter.pos.z + flashlightOffsetZ,
		1.0f
	};

	// Calculate direction based on the camera's position and look-at point
	GLfloat light_direction[] = {
		camera.lookX - camera.x,  // Direction in X
		camera.lookY - camera.y,  // Direction in Y
		camera.lookZ - camera.z   // Direction in Z
	};

	// Normalize direction
	float length = sqrt(light_direction[0] * light_direction[0] +
		light_direction[1] * light_direction[1] +
		light_direction[2] * light_direction[2]);

	light_direction[0] /= length;
	light_direction[1] /= length;
	light_direction[2] /= length;

	// Enhanced light properties during runtime
	GLfloat enhanced_diffuse[] = { 5.0f, 5.0f, 5.0f, 1.0f };
	GLfloat enhanced_specular[] = { 5.0f, 5.0f, 5.0f, 1.0f };

	glLightfv(FLASHLIGHT_LIGHT, GL_POSITION, light_position);
	glLightfv(FLASHLIGHT_LIGHT, GL_SPOT_DIRECTION, light_direction);
	glLightfv(FLASHLIGHT_LIGHT, GL_DIFFUSE, enhanced_diffuse);
	glLightfv(FLASHLIGHT_LIGHT, GL_SPECULAR, enhanced_specular);
}

// Function to calculate deltaTime (time difference between frames)
void Game::calculateDeltaTime() {
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsed = now - lastTime;
	deltaTime = elapsed.count();
	lastTime = now;
}


void Game::updateZombies() {
	const float ZOMBIE_SPEED = 0.000005f;  // Adjust this value to control zombie movement speed
	const float MIN_DISTANCE = 3.0f;   // Minimum distance to keep from player

	for (int i = 0; i < zombies.size(); i++) {
		// Calculate direction vector from zombie to player
		float dirX = shooter.pos.x - zombies[i].pos.x;
		float dirZ = shooter.pos.z - zombies[i].pos.z;

		// Calculate distance
		float distance = sqrt(dirX * dirX + dirZ * dirZ);

		// Only move if we're further than minimum distance
		if (distance > MIN_DISTANCE) {
			// Normalize direction vector
			dirX /= distance;
			dirZ /= distance;

			// Update zombie position
			zombies[i].pos.x += dirX * ZOMBIE_SPEED;
			zombies[i].pos.z += dirZ * ZOMBIE_SPEED;

			// Calculate rotation angle for zombie to face player
			float angle = atan2(dirX, dirZ) * (180.0f / M_PI);
			zombies[i].rot.y = angle;
		}

		// Optional: Add simple collision detection between zombies
		for (int j = 0; j < zombies.size(); j++) {
			if (i != j) {
				float zx = zombies[i].pos.x - zombies[j].pos.x;
				float zz = zombies[i].pos.z - zombies[j].pos.z;
				float zDist = sqrt(zx * zx + zz * zz);

				// If zombies are too close, push them apart slightly
				if (zDist < 1.0f) {
					zombies[i].pos.x += (zx / zDist) * 0.1f;
					zombies[i].pos.z += (zz / zDist) * 0.1f;
				}
			}
		}
	}
}

void Game::updateCamera() {
	// Player position
	Vector3f playerPos = { shooter.pos.x, shooter.pos.y, shooter.pos.z };
	Vector3f cameraOffset;
	Vector3f forwardOffset;
	Vector3f lookDirection;

	// Compute the direction vector based on the player's rotation
	float cosPitch = cosf(shooter.rot.x * M_PI / 180.0f);
	float sinPitch = sinf(shooter.rot.x * M_PI / 180.0f);
	float cosYaw = cosf(shooter.rot.y * M_PI / 180.0f);
	float sinYaw = sinf(shooter.rot.y * M_PI / 180.0f);

	// Calculate the forward direction vector the player is facing
	lookDirection.x = cosPitch * sinYaw;
	lookDirection.y = sinPitch;
	lookDirection.z = cosPitch * cosYaw;

	if (camera.isThirdPerson) {
		// Position the camera behind the player
		cameraOffset = Vector3f(
			-lookDirection.x * 10.0f,  // Move back in X
			8.5f,                      // Fixed camera height
			-lookDirection.z * 10.0f   // Move back in Z
		);
		// Look ahead of the player in their facing direction
		forwardOffset = playerPos + lookDirection * 10.0f;
	}
	else {
		// First-person camera: slightly above the player's head
		cameraOffset = Vector3f(0.0f, 7.5f, 3.0f);
		forwardOffset = playerPos + lookDirection * 25.0f;
	}

	// Set the camera position and look-at point
	camera.x = playerPos.x + cameraOffset.x;
	camera.y = playerPos.y + cameraOffset.y;
	camera.z = playerPos.z + cameraOffset.z;

	camera.lookX = forwardOffset.x;
	camera.lookY = forwardOffset.y;
	camera.lookZ = forwardOffset.z;
}


void handleOpenDoor(Shooter shooter) {
	bool doorIsOpening = getIsDoorOpening();
	float doorAngle = getDoorAngle();
	if (!doorIsOpening && doorAngle < 90.0f && shooter.hasKey) {
		setDoorOpening(true);
		int doorLastTime = glutGet(GLUT_ELAPSED_TIME);
		setDoorLastTime(doorLastTime);
	}
}



void Game::handleKeyPress(unsigned char key, int x, int y) {
	key = std::tolower(key);
	switch (key) {
	case 'w':
		shooter.moveForward();
		break;
	case 's':
		shooter.moveBackward();
		break;
	case 'a':
		shooter.moveLeft();
		break;
	case 'd':
		shooter.moveRight();
		break;
	case ' ':
		break;
	case 'c':
		break;
	case 't':
		break;
	case 'y':
		break;
	case 'u':
		break;
	case 'p':
		camera.toggleThirdPerson();
		break;
	case 'f':
		isFlashlightOn = !isFlashlightOn;
		break;
	case 'e':
		handleOpenDoor(shooter);
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
