#include <Headers/Bullet.h>
#include <Headers/Model_3DS.h>
#include <cmath>
#include <iostream>

#define speed 0.1f
#define M_PI 3.14159265358979323846

Bullet::Bullet(float x, float y, float z, float rotX, float rotY, float rotZ, float scale)
    : Model_3DS(x, y, z, rotX, rotY, rotZ, scale) {
    Load("Assets/models/Bullet/Bullet.3ds");
}


Bullet::Bullet() : Model_3DS(0,0,0,0,0,0,0) {
    Load("Assets/models/Bullet/Bullet.3ds");
}

void Bullet::update() {
    // Convert rotation angles from degrees to radians
    float rotYRad = rot.y * M_PI / 180.0f;
    float rotXRad = rot.x * M_PI / 180.0f;

    // Update position based on rotation angles
    pos.x += sin(rotYRad) * cos(rotXRad) * speed;
    pos.y += -sin(rotXRad) * speed;  // Negative because Y rotation is inverted in OpenGL
    pos.z += cos(rotYRad) * cos(rotXRad) * speed;
}

