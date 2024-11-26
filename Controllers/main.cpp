#include "Headers/Model_3DS.h"
#include "Headers/GLTexture.h"
#include "Headers/RenderEnviroment.h"
#include "Headers/Camera.h"
#include "Headers/Game.h"
#include <glut.h>

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
	// First light - Color changing spotlight
	GLfloat r = (sin(colorTimer) + 1.0f) / 2.0f;
	GLfloat g = (sin(colorTimer + 2.0944f) + 1.0f) / 2.0f;
	GLfloat b = (sin(colorTimer + 4.18879f) + 1.0f) / 2.0f;

	GLfloat coloredLight[] = { r, g, b, 1.0f };
	GLfloat light0_position[] = { 0.0f, 5.0f, -5.0f, 1.0f };
	GLfloat light0_direction[] = { 0.0f, -1.0f, 0.0f }; // Points straight down

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);         // 45-degree spotlight cone
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);        // How focused the spotlight is
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);  // Controls how quickly light fades with distance
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, coloredLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, coloredLight);

	// Second light - Blinking spotlight
	blinkTimer += 0.016f;
	if (blinkTimer >= BLINK_INTERVAL) {
		secondLightOn = !secondLightOn;
		blinkTimer = 0.0f;
	}

	GLfloat light1_position[] = { 0.0f, 10.0f, 5.0f, 1.0f };
	GLfloat light1_direction[] = { 0.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.02f);

	if (secondLightOn) {
		glEnable(GL_LIGHT1);
		GLfloat light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
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

	// First light setup
	GLfloat ambient0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light0_position[] = { 0.0f, 10.0f, -5.0f, 1.0f };
	GLfloat light0_direction[] = { 0.0f, 0.0f, -1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);

	// Second light setup
	GLfloat light1_position[] = { 0.0f, 15.0f, 10.0f, 1.0f };
	GLfloat light1_direction[] = { 0.0f, -1.0f, 0.0f };
	GLfloat ambient1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.02f);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	centerMouse();

	glutMainLoop();
}