#ifndef SOUND_H
#define SOUND_H

#include <string>

// Function to play a sound (cross-platform)
void playSound(const std::string& filePath);

// Function to play the gunshot sound
void playGunSound();
void playZombieDeathSound();
void playCoinSound();
void playKeySound();
void playMedkitCollectSound();
void playPlayerHitSound();
void playDoorSound();
void playUsingMedkitSound();
#endif // SOUND_H
