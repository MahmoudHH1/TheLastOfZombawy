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
    Vector3f eye, center, top;

    Cam(float X = 1.0f, float Y = 1.0f, float Z = 5.0f, float cenX = 0.0f, float cenY = 0.0f, float cenZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
        eye = Vector3f(X, Y, Z);
        center = Vector3f(cenX, cenY, cenZ);
        top = Vector3f(upX, upY, upZ);
    }

    void look() {
        gluLookAt(
            eye.x, eye.y, eye.z,
            center.x, center.y, center.z,
            top.x, top.y, top.z
        );
    }

    void moveForward(float distance) {
        Vector3f view = (center - eye).unit();
        eye = eye + view * distance;
        center = center + view * distance;
    }

    void moveRight(float distance) {
        Vector3f view = (center - eye).unit();
        Vector3f right = view.cross(top).unit();
        eye = eye + right * distance;
        center = center + right * distance;
    }

    void moveUp(float distance) {
        eye = eye + top * distance;
        center = center + top * distance;
    }

    void rotateX(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = top.cross(view).unit();
        view = view * cos(DEG2RAD(a)) + top * sin(DEG2RAD(a));
        top = view.cross(right);
        center = eye + view;
    }

    void rotateY(float a) {
        Vector3f view = (center - eye).unit();
        Vector3f right = top.cross(view).unit();
        view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
        right = view.cross(top);
        center = eye + view;
    }

    void reset() {
        eye = Vector3f(1.0f, 1.0f, 5.0f);
        center = Vector3f(0.0f, 0.0f, 0.0f);
        top = Vector3f(0.0f, 1.0f, 0.0f);
    }
};


#endif