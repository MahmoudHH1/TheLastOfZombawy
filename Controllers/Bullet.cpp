#include <Headers/Bullet.h>
#include <Headers/Model_3DS.h>
#include <cmath>
#include <iostream>

#define speed 0.001f
#define M_PI 3.14159265358979323846

Bullet::Bullet(float x, float y, float z, float rotX, float rotY, float rotZ , float scale)
	: Model_3DS(x , y , z , rotX , rotY , rotZ , scale) {
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



void Bullet::Draw() {
    // Save current matrix state
    glPushMatrix();

    // Apply transformations
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rot.y, 0, 1, 0);  // Apply yaw rotation
    glRotatef(rot.x, 1, 0, 0);  // Apply pitch rotation
    glScalef(0.1f, 0.1f, 0.1f);

    // Save attributes
    glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT);

    // Set material properties for the bullet (red color)
    GLfloat bulletColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };  // Red color
    GLfloat bulletShininess[] = { 50.0f };               // Shininess value

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bulletColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bulletColor);
    glMaterialfv(GL_FRONT, GL_SHININESS, bulletShininess);

    // Apply scaling for the bullet
    float bulletLength = 20.0f;    // Length of the bullet
    float bulletRadius = 5.0f;     // Radius of the bullet

    // Draw bullet body (cylinder)
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    // Draw cylinder body
    gluCylinder(quadric, bulletRadius, bulletRadius, bulletLength, 12, 1);

    // Draw bullet tip (cone)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, bulletLength);
    gluCylinder(quadric, bulletRadius, 0.0f, bulletRadius * 2, 12, 1);
    glPopMatrix();

    // Draw base cap
    gluDisk(quadric, 0.0f, bulletRadius, 12, 1);

    // Clean up
    gluDeleteQuadric(quadric);

    // Restore attributes
    glPopAttrib();

    // Restore original matrix state
    glPopMatrix();
}
