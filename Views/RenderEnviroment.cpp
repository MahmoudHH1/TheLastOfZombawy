#include "TextureBuilder.h"
#include "Headers/RenderEnviroment.h"
#include "Headers/GLTexture.h"
#include "glut.h"


GLuint groundTex_1;
GLuint groundTex_2;
GLTexture groundTexture_1;
GLTexture groundTexture_2;

GLuint wallTex_1;
GLuint wallTex_2;
GLuint wallTex_3;
GLTexture wallTexture_1;
GLTexture wallTexture_2;
GLTexture wallTexture_3;

GLuint ceilingTex_1;
GLuint ceilingTex_2;
GLTexture ceilingTexture_1;
GLTexture ceilingTexture_2;

bool isDoorOpen = true ;

void RenderTexturedCube(GLuint texture);

void loadEnvironmentAssets() {

	wallTexture_1.Load("Assets/textures/wall_1.bmp");
	loadBMP(&wallTex_1, "Assets/textures/wall_1.bmp", true);

	wallTexture_2.Load("Assets/textures/wall_2.bmp");
	loadBMP(&wallTex_2, "Assets/textures/wall_2.bmp", true);

	wallTexture_3.Load("Assets/textures/wall_3.bmp");
	loadBMP(&wallTex_3, "Assets/textures/wall_3.bmp", true);

	groundTexture_1.Load("Assets/textures/ground_1.bmp");
	loadBMP(&groundTex_1, "Assets/textures/ground_1.bmp", true);

	groundTexture_2.Load("Assets/textures/ground_2.bmp");
	loadBMP(&groundTex_2, "Assets/textures/ground_2.bmp", true);

	ceilingTexture_1.Load("Assets/textures/ceiling_1.bmp");
	loadBMP(&ceilingTex_1, "Assets/textures/ceiling_1.bmp", true);

	ceilingTexture_2.Load("Assets/textures/ceiling_2.bmp");
	loadBMP(&ceilingTex_2, "Assets/textures/ceiling_2.bmp", true);
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

void RenderGround(GLTexture groundTexture)
{
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

void RenderCeiling(GLTexture ceilingTexture) {

	//glDisable(GL_LIGHTING);	// Disable lighting
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	//glColor3f(0.2, 0.2, 0.2);
	glBindTexture(GL_TEXTURE_2D, ceilingTexture.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1, 1, 1);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-1, 0, -1);
	glTexCoord2f(5, 0);
	glVertex3f(1, 0, -1);
	glTexCoord2f(5, 5);
	glVertex3f(1, 0, 1);
	glTexCoord2f(0, 5);
	glVertex3f(-1, 0, 1);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.
	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}


void renderTexturedWall(GLTexture wallTexture) {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, wallTexture.texture[0]);
	glPushMatrix();
	
	glTranslatef(0, 0, 0);
	glScalef(1, 1, 1);
	
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0); 
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 0);
	glEnd();
	
	glPopMatrix();
}

void renderLevel1World() {
	// wall on the right
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(17.2, 1, -40);
	glScalef(23, 15, 1);
	renderTexturedWall(wallTexture_1);
	glPopMatrix();


	// wall on the left
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(17.2, 1, 40);
	glScalef(23, 15, 1);
	renderTexturedWall(wallTexture_1);
	glPopMatrix();


	// wall behind me
	glPushMatrix();
	glTranslatef(0, 1, -40);
	glScalef(40, 15, 1);
	renderTexturedWall(wallTexture_1);
	glPopMatrix();


	// the ceiling
	glPushMatrix();
	glTranslatef(-10, 12, -25);
	glScalef(50, 1, 30);
	RenderCeiling(ceilingTexture_1);
	glPopMatrix();
	
	// the ground
	glPushMatrix();
	glTranslatef(0, 0, -15);
	glScalef(2, 1, 1);
	RenderGround(groundTexture_1);
	glPopMatrix();
}

void renderMiddleWall() {
	
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wallTexture_3.texture[0]);

	glPushMatrix();

	// Top quad
	glPushMatrix();
	glTranslatef(0, 10.5, 5);
	glScalef(40, 2, 1);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0.8); // Top-left of the texture
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 0.8); // Top-right of the texture
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 1);   // Bottom-right of the texture
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 1);   // Bottom-left of the texture
	glVertex3f(-1, 1, 0);
	glEnd();
	glPopMatrix();

	// Left quad
	glPushMatrix();
	glTranslatef(-23, 3.5, 5);
	glScalef(20, 5, 1);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0.5); // Top-left of the texture
	glVertex3f(-1, -1, 0);
	glTexCoord2f(0.5, 0.5); // Top-right of the texture
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.5, 0.8); // Bottom-right of the texture
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 0.8);   // Bottom-left of the texture
	glVertex3f(-1, 1, 0);
	glEnd();
	glPopMatrix();

	// Right quad
	glPushMatrix();
	glTranslatef(23, 3.5, 5);
	glScalef(20, 5, 1);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.5, 0.5); // Top-left of the texture
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 0.5);   // Top-right of the texture
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 0.8);   // Bottom-right of the texture
	glVertex3f(1, 1, 0);
	glTexCoord2f(0.5, 0.8); // Bottom-left of the texture
	glVertex3f(-1, 1, 0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}



void renderLevel2World() {

	//wall on right
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-25, 1, -38.5);
	glScalef(20, 15, 1);
	renderTexturedWall(wallTexture_2);
	glPopMatrix();

	//wall on left
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-25, 1, 38.5);
	glScalef(20, 15, 1);
	renderTexturedWall(wallTexture_2);
	glPopMatrix();


	// wall in front
	glPushMatrix();
	glTranslatef(0, 1, 40);
	glScalef(40, 15, 1);
	renderTexturedWall(wallTexture_2);
	glPopMatrix();


	// Render the ground
	glPushMatrix();
	glColor3f(0.58, 0.3, 0);
	glTranslatef(0, 0, 25);
	glScalef(2, 1, 1);
	RenderGround(groundTexture_2);
	glPopMatrix();


	// the ceiling
	glPushMatrix();
	glTranslatef(-10, 12, 30);
	glScalef(50, 1, 25);
	RenderCeiling(ceilingTexture_2);
	glPopMatrix();
	
	glColor3f(1, 1, 1); // reseting the color to white
}

// Function to render the environment
void RenderEnvironment() {
	
	renderLevel1World();

	renderMiddleWall();

	renderLevel2World();

	//// Render the door
	//glPushMatrix();
	//glTranslatef(8.0, 0, -40); // Align the door to the middle wall
	//RenderDoor();
	//glPopMatrix();
	//glPopMatrix();

	// Render steps inside the room
	RenderSteps();

}

void openDoor() {
	isDoorOpen = true;
}