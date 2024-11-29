#include "Headers/Model_3DS.h"
#include "Headers/GLTexture.h"
#include "Headers/RenderEnviroment.h"
#include "Headers/Camera.h"
#include "Headers/Game.h"
#include <glut.h>

#define FLASHLIGHT_LIGHT GL_LIGHT2  // Using LIGHT2 for the flashlight

int WIDTH = 1280;
int HEIGHT = 720;

//float camMoveSpeed = 0.05f; // Camera movement speed

//GLuint tex;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;

// Add these global variables at the top of your file
float colorTimer = 0.0f;
bool secondLightOn = true;
float blinkTimer = 0.0f;
const float BLINK_INTERVAL = 1.0f; // 1 second interval for blinking
const float COLOR_CHANGE_SPEED = 0.01f;

//Cam camera;
Game game;
//bool keys[256] = { false };




void centerMouse() {
	POINT windowCenter;
	windowCenter.x = WIDTH / 2;
	windowCenter.y = HEIGHT / 2;
	ClientToScreen(GetActiveWindow(), &windowCenter);
	SetCursorPos(windowCenter.x, windowCenter.y);
}

void MouseMovement(int x, int y) {
	if (game.camera.isMouseLocked) {
		int dx = x - WIDTH / 2;
		int dy = y - HEIGHT / 2;

		float sensitivity = -0.01f;
		game.camera.rotateY(dx * sensitivity);
		game.camera.rotateX(dy * sensitivity);

		centerMouse();
	}

	glutPostRedisplay();
}

void cam() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)WIDTH / (float)HEIGHT, 0.001, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	game.camera.look();
}



void updateLights() {
	// First light - Color changing spotlight with increased intensity
	GLfloat r = ((sin(colorTimer) + 1.0f) / 2.0f) * 2.0f; // Doubled intensity
	GLfloat g = ((sin(colorTimer + 2.0944f) + 1.0f) / 2.0f) * 2.0f;
	GLfloat b = ((sin(colorTimer + 4.18879f) + 1.0f) / 2.0f) * 2.0f;
	GLfloat coloredLight[] = { r, g, b, 1.0f };
	GLfloat light0_position[] = { 0.0f, 15.0f, 2.0f, 1.0f };
	GLfloat light0_direction[] = { 0.0f, 0.0f, -1.0f };

	// Reduced attenuation for farther light reach
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);         // Wider angle
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);        // Less focused for broader illumination
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f); // Reduced from 1.0
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02f);  // Reduced from 0.05
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f); // Removed quadratic attenuation

	// Increased light intensity
	GLfloat brightColoredLight[] = { r * 3.0f, g * 3.0f, b * 3.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, brightColoredLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, brightColoredLight);

	// Second light - Brighter blinking spotlight
	blinkTimer += 0.016f;
	if (blinkTimer >= BLINK_INTERVAL) {
		secondLightOn = !secondLightOn;
		blinkTimer = 0.0f;
	}

	GLfloat light1_position[] = { 0.0f, 15.0f, 2.0f, 1.0f };
	GLfloat light1_direction[] = { 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f);         // Wider angle
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);        // Less focused
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5f);  // Reduced
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02f);   // Reduced
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f); // Removed

	if (secondLightOn) {
		glEnable(GL_LIGHT1);
		GLfloat light1_diffuse[] = { 3.0f, 3.0f, 3.0f, 1.0f }; // Tripled intensity
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	}
	else {
		glDisable(GL_LIGHT1);
	}

	colorTimer += COLOR_CHANGE_SPEED;
}

void InitLightSource() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// First light setup with increased ambient and brighter initial settings
	GLfloat ambient0[] = { 0.3f, 0.3f, 0.3f, 1.0f };    // Increased ambient
	GLfloat light0_position[] = { 0.0f, 15.0f, 2.0f, 1.0f };
	GLfloat light0_direction[] = { 0.0f, 0.0f, -1.0f };
	GLfloat diffuse0[] = { 3.0f, 3.0f, 3.0f, 1.0f };    // Bright diffuse
	GLfloat specular0[] = { 3.0f, 3.0f, 3.0f, 1.0f };   // Bright specular

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);

	// Second light setup with increased brightness
	GLfloat light1_position[] = { 0.0f, 15.0f, 2.0f, 1.0f };
	GLfloat light1_direction[] = { 0.0f, 0.0f, 1.0f };
	GLfloat ambient1[] = { 0.3f, 0.3f, 0.3f, 1.0f };     // Increased ambient
	GLfloat diffuse1[] = { 3.0f, 3.0f, 3.0f, 1.0f };     // Tripled intensity
	GLfloat specular1[] = { 3.0f, 3.0f, 3.0f, 1.0f };    // Tripled intensity

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	//flashlight 
	glEnable(GL_LIGHT2);
	GLfloat flashlight_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };     // Increased ambient
	GLfloat flashlight_diffuse[] = { 5.0f, 5.0f, 5.0f, 1.0f };     // Much brighter diffuse
	GLfloat flashlight_specular[] = { 5.0f, 5.0f, 5.0f, 1.0f };    // Much brighter specular

	glLightfv(FLASHLIGHT_LIGHT, GL_AMBIENT, flashlight_ambient);
	glLightfv(FLASHLIGHT_LIGHT, GL_DIFFUSE, flashlight_diffuse);
	glLightfv(FLASHLIGHT_LIGHT, GL_SPECULAR, flashlight_specular);

	// Set flashlight properties for more focused beam
	glLightf(FLASHLIGHT_LIGHT, GL_SPOT_CUTOFF, 25.0f);        // Narrower beam angle
	glLightf(FLASHLIGHT_LIGHT, GL_SPOT_EXPONENT, 40.0f);      // More focused spotlight
	glLightf(FLASHLIGHT_LIGHT, GL_CONSTANT_ATTENUATION, 0.5f); // Reduced constant attenuation
	glLightf(FLASHLIGHT_LIGHT, GL_LINEAR_ATTENUATION, 0.02f);  // Reduced linear attenuation
	glLightf(FLASHLIGHT_LIGHT, GL_QUADRATIC_ATTENUATION, 0.0f);// Removed quadratic attenuation
}


//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);

	game = Game();
}


//=======================================================================
// Display Function
//=======================================================================
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//controlKeyboard();


	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	updateLights();

	game.Draw();
	cam();

	glutSwapBuffers();
}



void handleUserInput(unsigned char key, int x, int y) {
	game.handleKeyPress(key, x, y);
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void updateGame() {
	game.update();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(draw);

	glutKeyboardFunc(handleUserInput);
	//glutKeyboardUpFunc(KeyboardUp);
	glutPassiveMotionFunc(MouseMovement);
	glutSetCursor(GLUT_CURSOR_NONE);

	
	glutReshapeFunc(myReshape);

	init();

	glutIdleFunc(updateGame);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	centerMouse();

	glutMainLoop();
}