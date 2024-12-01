#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <glut.h>

#define DEG2RAD(a) (a * 0.0174532925)

class Vector3f {
public:
    float x, y, z;

    Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f operator+(Vector3f& v) {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }

    Vector3f operator-(Vector3f& v) {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }

    Vector3f operator*(float n) {
        return Vector3f(x * n, y * n, z * n);
    }

    Vector3f operator/(float n) {
        return Vector3f(x / n, y / n, z / n);
    }

    Vector3f unit() {
        return *this / sqrt(x * x + y * y + z * z);
    }

    Vector3f cross(Vector3f v) {
        return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};

class Cam {
public:
    float x, y, z; // Camera position
    float lookX, lookY, lookZ; // Look-at direction
    bool isMouseLocked;

    bool isThirdPerson = false;

    Cam(float X = 1.0f, float Y = 1.0f, float Z = 5.0f, float lookX = 0.0f, float lookY = 0.0f, float lookZ = 0.0f) {
        this->x = X;
        this->y = Y;
        this->z = Z;
        this->lookX = lookX;
        this->lookY = lookY;
        this->lookZ = lookZ;
        isMouseLocked = true;
    }

    void look() {
        gluLookAt(
            x, y, z,
            lookX, lookY, lookZ,
            0.0f, 1.0f, 0.0f // Keep the camera upright with the global "up" vector
        );
    }

    void rotateX(float a) {
        Vector3f view(lookX - x, lookY - y, lookZ - z);
        Vector3f right = Vector3f(0.0f, 1.0f, 0.0f).cross(view).unit();
        view = view * cos(DEG2RAD(a)) + Vector3f(0.0f, 1.0f, 0.0f) * sin(DEG2RAD(a));
        lookX = x + view.x;
        lookY = y + view.y;
        lookZ = z + view.z;
    }

    void rotateY(float a) {
        Vector3f view(lookX - x, lookY - y, lookZ - z);
        Vector3f right = Vector3f(0.0f, 1.0f, 0.0f).cross(view).unit();
        view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
        lookX = x + view.x;
        lookY = y + view.y;
        lookZ = z + view.z;
    }

    void reset() {
        x = 1.0f;
        y = 1.0f;
        z = 5.0f;
        lookX = 0.0f;
        lookY = 0.0f;
        lookZ = 0.0f;
    }

    //void followPlayer(Vector3f playerPos, Vector3f offset) {
    //    // Set the camera position relative to the player
    //    x = playerPos.x + offset.x;
    //    y = playerPos.y + offset.y;
    //    z = playerPos.z + offset.z;

    //    // Set the look direction to the player's position
    //    lookX = playerPos.x;
    //    lookY = playerPos.y;
    //    lookZ = playerPos.z;
    //}

    void toggleThirdPerson() {
        isThirdPerson = !isThirdPerson;
    }
};

#endif
