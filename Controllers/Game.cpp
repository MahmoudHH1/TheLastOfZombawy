#include "Headers/Model_3DS.h"
#include "Headers/GLTexture.h"
#include "Headers/RenderEnviroment.h"
#include "Headers/Camera.h"
#include <glut.h>

int WIDTH = 1280;
int HEIGHT = 720;

float camMoveSpeed = 0.05f; // Camera movement speed

//GLuint tex;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;

Cam camera;
bool isMouseLocked = true; // Flag to lock the mouse inside
bool keys[256] = { false };

void centerMouse() {
	POINT windowCenter;
	windowCenter.x = WIDTH / 2;
	windowCenter.y = HEIGHT / 2;
	ClientToScreen(GetActiveWindow(), &windowCenter);
	SetCursorPos(windowCenter.x, windowCenter.y);
}

void MouseMovement(int x, int y) {
	if (isMouseLocked) {
		int dx = x - WIDTH / 2;
		int dy = y - HEIGHT / 2;

		float sensitivity = -0.1f;
		camera.rotateY(dx * sensitivity);
		camera.rotateX(dy * sensitivity);

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
	camera.look();
}

void Keyboard(unsigned char key, int x, int y) {
	keys[key] = true;  // Set the key state to true when the key is pressed
}

void KeyboardUp(unsigned char key, int x, int y) {
	keys[key] = false;  // Set the key state to false when the key is released
}


void controlKeyboard() {
	if (keys['w']) {
		camera.moveForward(camMoveSpeed);
	}
	if (keys['s']) {
		camera.moveForward(-camMoveSpeed);
	}
	if (keys['a']) {
		camera.moveRight(-camMoveSpeed);
	}
	if (keys['d']) {
		camera.moveRight(camMoveSpeed);
	}
	if (keys[' ']) {
		camera.moveUp(camMoveSpeed);
	}
	if (keys['c']) {
		camera.moveUp(-camMoveSpeed);
	}
	if (keys['t']) {
		camera.eye = Vector3f(0, 5, 0);
		camera.center = Vector3f(0, 0, 0);
		camera.top = Vector3f(0, 0, -1);
	}
	if (keys['y']) {
		camera.eye = Vector3f(5, 0, 0);
		camera.center = Vector3f(0, 0, 0);
		camera.top = Vector3f(0, 1, 0);
	}
	if (keys['u']) {
		camera.eye = Vector3f(0, 0, 5);
		camera.center = Vector3f(0, 0, 0);
		camera.top = Vector3f(0, 1, 0);
	}
	if (keys[27]) {
		isMouseLocked = false;
		exit(EXIT_SUCCESS);
	}
}

//// Model Variables
//Model_3DS model_house;
//Model_3DS model_tree;
//
//Model_3DS model_shooter;
//Model_3DS model_zombie;
//Model_3DS model_bigBoss;


//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
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
void myInit(void)
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
}


//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	controlKeyboard();


	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	cam();

	RenderEnvironment();


	//// Draw Tree Model
	//glPushMatrix();
	//glTranslatef(10, 0, 0);
	//glScalef(0.7, 0.7, 0.7);
	//model_tree.Draw();
	//glPopMatrix();

	//// Draw house Model
	//glPushMatrix();
	//glRotatef(90.f, 1, 0, 0);
	//model_house.Draw();
	//glPopMatrix();






	glutSwapBuffers();
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

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	loadEnvironmentAssets();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutPassiveMotionFunc(MouseMovement);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	centerMouse();

	glutMainLoop();
}