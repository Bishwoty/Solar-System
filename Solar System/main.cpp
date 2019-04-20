#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "planet.h"
using namespace std;

const float PI = 3.141592654;

// Window Options
int WindowWidth = 1000;
int WindowHeight = 1000;
const char* WindowName = "Solar Sim";

int WindowID;

// LookAt
double eyex = 0.0;
double eyey = 0.0;
double eyez = 400.0;
double atx = 0.0;
double aty = 0.0;
double atz = 0.0;
double upx = 0.0;
double upy = 1.0;
double upz = 0.0;

// Camera
double camRotateVertical = 30;
double camRotateHorizontal = 0;
double camPanHorizontal = 0;
double camPanVertical = 0;
double camZoom = 0;

// Scaleing
double timeScale = 0.5;
double planetScale = 0.40;
double sunScale = 0.010;
double orbitScale = 0.001;
double moonScale = 0.2;

// Toggles
bool showOrbits = true;

// Objects
planet sun(695.508, 0, 1, 0.9, 0.1, 0.1);

// Callback Functions
void Display();
void Reshape(int width, int height);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Idle();
void Special(int key, int x, int y);

void init(int &argc, char ** argv);
void createPlanets();
void PrintString(int x, int y, void *font, int fontSize, int lineBuffer, string str);
void changeAngle(double & var, double angle);
void drawPlanet(planet & origin);
void tick(planet & origin);

// Shapes
void createSphere(float radius);
void createCircle(float radius, int segments);


int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WindowWidth, WindowHeight);
	WindowID = glutCreateWindow(WindowName);
	glutDisplayFunc(&Display);
	glutIdleFunc(&Idle);
	glutReshapeFunc(&Reshape);
	glutMouseFunc(&Mouse);
	glutKeyboardFunc(&Keyboard);
	glutSpecialFunc(&Special);
	init(argc, argv);
	glutMainLoop();
	return 0;
}

void init(int &argc, char ** argv) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	createPlanets();
}

void createPlanets() {
	sun.addMoon("mercury", 2.4937, 57909.227, 0.2408467, 0.5, 0.5, 0.5);
	sun.addMoon("venus", 6.0518, 108209.475, 0.61519726, 0.949, 0.808, 0.255);
	sun.addMoon("earth", 6.371, 149598.262, 1.0000174, 0.1, 0.1, 0.8);
	sun.moon("earth").addMoon("theMoon", 1.7375, 384.4, 0.074745, 0.8, 0.8, 0.8);
	sun.addMoon("mars", 3.3895, 227943.824, 1.88108476, 1, 0, 0);
}

void PrintString(int x, int y, void *font, int fontSize, int lineBuffer, string str) {
	int lineNumber = 0;
	vector<string> myLines;
	for(int i = str.find('\n'); i != string::npos; i = str.find('\n')) {
		myLines.push_back(str.substr(0, i));
		str.erase(0, i + 1);
	}
	myLines.push_back(str);
	for(int i = 0; i < myLines.size(); i++) {
		glRasterPos2i(x, y - fontSize * lineNumber - lineBuffer * (lineNumber - 1));
		for(int j = 0; j < myLines[i].length(); j++)
			glutBitmapCharacter(font, myLines[i][j]);
		lineNumber++;
	}
}

void Idle() {
	tick(sun);
	
	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_UP:
		camPanVertical += 1;
		break;
	case GLUT_KEY_LEFT:
		camPanHorizontal -= 1;
		break;
	case GLUT_KEY_DOWN:
		camPanVertical -= 1;
		break;
	case GLUT_KEY_RIGHT:
		camPanHorizontal += 1;
		break;
	case GLUT_KEY_PAGE_UP:
		camZoom += 1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		camZoom -= 1;
		break;
	case GLUT_KEY_F1:
		showOrbits = !showOrbits;
		break;
	}
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		glutDestroyWindow(WindowID);
		break;
	case 'w':
		changeAngle(camRotateVertical, 1);
		break;
	case 'a':
		changeAngle(camRotateHorizontal, 1);
		break;
	case 's':
		changeAngle(camRotateVertical, -1);
		break;
	case 'd':
		changeAngle(camRotateHorizontal, -1);
		break;
	default:
		break;
	}
}

void Mouse(int button, int state, int x, int y) {
	switch(button) {
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN) {

		}
		if(state == GLUT_UP) {

		}
		break;

	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN) {

		}
		if(state == GLUT_UP) {

		}
		break;
	}
}

void createSphere(float radius) {
	glutSolidSphere(radius, 100, 100);
}

void createCircle(float radius, int segments){
	float x, y, theta;
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < segments; i++) {
		theta = 2 * PI * i / segments;
		x = radius * cos(theta);
		y = radius * sin(theta);
		
		glVertex3f(x, 0, y);
	}
	glEnd();
}

void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WindowWidth, WindowHeight);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluPerspective(63, double(WindowWidth) / double(WindowHeight), 1, 1000);
	//glFrustum(-10, 10, -10, 10, 20, 1000);
	gluLookAt(eyex, eyey, eyez, atx, aty, atz, upx, upy, upz);

	glTranslatef(-camPanHorizontal, -camPanVertical, camZoom);
	glRotatef(camRotateVertical, 1, 0, 0);
	glRotatef(camRotateHorizontal, 0, 1, 0);

	//DRAW
	glPushMatrix();
	glColor3f(sun.red(), sun.green(), sun.blue());
	createSphere(sun.radius()*sunScale);
	glPopMatrix();
	for(auto it = sun.begin(); it != sun.end(); ++it)
		drawPlanet(it -> second);

	// Text
	glViewport(0, 0, WindowWidth, WindowHeight);
	glLoadIdentity();
	gluOrtho2D(0, WindowWidth, 0, WindowHeight);
	string text = "CamPanX: " + to_string(camPanHorizontal) + "\nCamPanY: " + to_string(camPanVertical) + "\nr: " + to_string(sqrt(pow(eyex, 2) + pow(eyez, 2))) + "\nTheta: ";
	glColor3f(1, 1, 1);
	PrintString(2, WindowHeight - 14, GLUT_BITMAP_HELVETICA_12, 12, 2, text);

	glutSwapBuffers();
}

void Reshape(int width, int height) {
	WindowWidth = width;
	WindowHeight = height;
}

void changeAngle(double & var, double angle) {
	var += angle;
	while(var > 360)
		var -= 360;
	while(var < 0)
		var += 360;
}

void drawPlanet(planet & origin) {
	glPushMatrix();
	if(showOrbits) {
		glColor3f(0, 1, 0);
		createCircle(origin.distance() * orbitScale, 50);
	}
	glColor3f(origin.red(), origin.green(), origin.blue());
	glRotatef(origin.angularPosition(), 0, 1, 0);
	glTranslatef(origin.distance() * orbitScale, 0, 0);
	createSphere(origin.radius()*planetScale);
	for(auto it = origin.begin(); it != origin.end(); ++it) {
		glPushMatrix();
		glRotatef(it -> second.angularPosition(), 0, 1, 0);
		glTranslatef(it -> second.distance() * planetScale * moonScale, 0, 0);
		glColor3f(it -> second.red(), it -> second.red(), it -> second.blue());
		createSphere(it -> second.radius()*planetScale);
		glPopMatrix();
	}
	glPopMatrix();
}

void tick(planet & origin) {
	origin.orbit((1 / origin.period()) * timeScale);
	for(auto it = origin.begin(); it != origin.end(); ++it) {
		tick(it->second);

	}
}
