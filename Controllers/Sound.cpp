#include "Headers/Sound.h"
#include <iostream>
#include <cstdlib>

#if defined(_WIN32) || defined(_WIN64) // Windows-specific headers
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") // Link with the Windows multimedia library
#endif

// Function to play a sound asynchronously (Windows-specific)
void playSound(const std::string& filePath) {
    if (!PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
        // If the sound fails to play, print an error message
        std::cerr << "Failed to play sound: " << filePath << std::endl;
    }
}

// Function to play the gunshot sound
void playGunSound() {
    playSound("Assets/sounds/gunShot.wav"); // Play the sound directly
}

void playZombieDeathSound() {
	playSound("Assets/sounds/zombieDeath.wav");
}

void playCoinSound() {
	playSound("Assets/sounds/coin.wav");
}

void playKeySound() {
	playSound("Assets/sounds/key.wav");
}

void playMedkitCollectSound() {
	playSound("Assets/sounds/medkitCollect.wav");
}

void playPlayerHitSound() {
	playSound("Assets/sounds/playerHit.wav");
}

void playDoorSound() {
	playSound("Assets/sounds/doorOpening.wav");
}

void playUsingMedkitSound() {
	playSound("Assets/sounds/heal.wav");
}