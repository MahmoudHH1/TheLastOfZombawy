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

void RenderEnvironment() {
	
	glPushMatrix();
	glTranslatef(-10, 0, -10);
	glPushMatrix();
	glTranslatef(0, 2.5, 10);
	glScalef(0.1, 5, 25);
	RenderWallLevel2();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, -10);
	glPushMatrix();
	glTranslatef(0, 2.5,  10);
	glScalef(0.1, 5, 25);
	RenderWallLevel2();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(10, 0, -10);
	glPushMatrix();
	glTranslatef(0, 2.5, 10);
	glScalef(0.1, 5, 25);
	RenderWallLevel2();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-10, 0, -10);
	glPushMatrix();
	glTranslatef(0, 2.5,  10);
	glScalef(0.1, 5, 25);
	RenderWallLevel2();
	glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
	glScalef(0.5, 1, 0.5);
	RenderGround();
	glPopMatrix();
}