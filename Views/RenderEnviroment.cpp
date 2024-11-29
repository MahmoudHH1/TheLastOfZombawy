#include "TextureBuilder.h"
#include "Headers/RenderEnviroment.h"
#include "Headers/GLTexture.h"
#include "glut.h"


GLuint groundTex;
GLTexture groundTexture;

GLuint wallTex_1;
GLuint wallTex_2;
GLTexture wallTexture_1;
GLTexture wallTexture_2;

bool isDoorOpen = false;

void RenderTexturedCube(GLuint texture);

void loadEnvironmentAssets() {

	wallTexture_1.Load("Assets/textures/wall-stone.bmp");
	loadBMP(&wallTex_1, "Assets/textures/wall-stone.bmp", true);

	wallTexture_2.Load("Assets/textures/wall-stone-2.bmp");
	loadBMP(&wallTex_2, "Assets/textures/wall-stone-2.bmp", true);

	groundTexture.Load("Assets/textures/ground-stone.bmp");
	loadBMP(&groundTex, "Assets/textures/ground-stone.bmp", true);
}


void RenderWallLevel1() {
	RenderTexturedCube(wallTex_1);
}

void RenderWallLevel2() {
	RenderTexturedCube(wallTex_2);
}


void RenderTexturedCube(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);

	// Front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// Top face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	// Bottom face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

	// Right face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);

	// Left face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();
}

void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, groundTexture.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

// Function to render the door
void RenderDoor() {
	glPushMatrix();
	if (isDoorOpen) {
		glTranslatef(2.0f, 0.0f, 0.0f); // Shift the door to simulate opening
	}
	glScalef(4.0f, 8.0f, 0.2f); // Door dimensions
	RenderWallLevel1();         // Use wall texture for the door
	glPopMatrix();
}

// Function to render steps
void RenderSteps() {
	// Step along the bottom wall
	glPushMatrix();
	glTranslatef(0, 0.5, -39.0); // Position the step near the wall
	glScalef(80, 6, 10);         // Adjust dimensions for the wall length
	RenderWallLevel1();
	glPopMatrix();

	// Step along the top wall
	glPushMatrix();
	glTranslatef(0, 0.5, 39.0);
	glScalef(80, 6, 10);
	RenderWallLevel1();
	glPopMatrix();

	// Step along the left wall
	glPushMatrix();
	glTranslatef(-39.0, 0.5, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(80, 6, 10);
	RenderWallLevel1();
	glPopMatrix();

	// Step along the right wall
	glPushMatrix();
	glTranslatef(39.0, 0.5, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(80, 6, 10);
	RenderWallLevel1();
	glPopMatrix();
}

// Function to render the environment
void RenderEnvironment() {
	// Outer walls
	glPushMatrix();
	glTranslatef(-40, 0, -40);
	glPushMatrix();
	glTranslatef(0, 4.5, 40);
	glScalef(0.2, 9, 90);
	RenderWallLevel2();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 0, -40);
	glPushMatrix();
	glTranslatef(0, 4.5, 40);
	glScalef(0.2, 9, 90);
	RenderWallLevel2();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(40, 0, -40);
	glPushMatrix();
	glTranslatef(0, 4.5, 40);
	glScalef(0.2, 9, 90);
	RenderWallLevel2();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-40, 0, -40);
	glPushMatrix();
	glTranslatef(0, 4.5, 40);
	glScalef(0.2, 9, 90);
	RenderWallLevel2();
	glPopMatrix();
	glPopMatrix();

	// Middle wall with a door
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, -40);
	glPushMatrix();
	glTranslatef(-8.0, 4.5, 40); // Offset for the door placement
	glScalef(0.2, 9, 76);        // Shortened wall length to fit the door
	RenderWallLevel1();
	glPopMatrix();

	// Render the door
	glPushMatrix();
	glTranslatef(8.0, 0, -40); // Align the door to the middle wall
	RenderDoor();
	glPopMatrix();
	glPopMatrix();

	// Render steps inside the room
	RenderSteps();

	// Render the ground
	glPushMatrix();
	glScalef(2, 1, 2);
	RenderGround();
	glPopMatrix();
}

void openDoor() {
	isDoorOpen = true;
}