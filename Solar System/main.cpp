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
#include <ctime>
#include <chrono>
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
double timeScale = 1;
double planetScale = 0.0001;
double sunScale = 1.00;
double orbitScale = 0.0001;
double moonScale = 1;
double modifier = 1;

// Toggles
bool showOrbits = true;
bool pause = false;
string followObject = "sun";

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
	srand(time(NULL));
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);
	createPlanets();
}

void createPlanets() {
	// Planet stats found at https://solarsystem.nasa.gov/planet-compare/
	// Radius in 1000s of kms
	// Orbital distance in 1000s of kms
	// Orbital Period in Earth Years

	// Planets
	sun.addMoon("mercury", 2.4937, 57909.227, 0.2408467, 0.5, 0.5, 0.5);
	sun.addMoon("venus", 6.0518, 108209.475, 0.61519726, 0.949, 0.808, 0.255);
	sun.addMoon("earth", 6.371, 149598.262, 1.0000174, 0.1, 0.1, 0.8);
	sun.addMoon("mars", 3.3895, 227943.824, 1.88108476, 1, 0, 0);
	sun.addMoon("jupiter", 69.911, 778340.821, 11.862615, 1, .4, .4);
	sun.addMoon("saturn", 58.232, 1426666.422, 29.447498, 1, 1, 0.8);
	sun.addMoon("uranus", 25.362, 2870658.186, 84.016846, 0.8, 0.8, 1);
	sun.addMoon("neptune", 24.622, 4498396.441, 164.79132, 0.2, 0.2, 1);

	// Moons
	sun.moon("earth").addMoon("the moon", 1.7375, 384.4, 0.074745, 0.8, 0.8, 0.8);
	sun.moon("jupiter").addMoon("io", 1.8216, 421.800, 0.00484, 1, 1, 1);
	sun.moon("jupiter").addMoon("europa", 1.5618, 671.100, 0.00972, 1, 1, 1);
	sun.moon("jupiter").addMoon("ganymede", 2.6312, 1070.400, 0.01948, 1, 1, 1);
	sun.moon("jupiter").addMoon("callisto", 2.4103, 1882.700, 0.04570, 1, 1, 1);
}

void PrintString(int x, int y, void *font, int fontSize, int lineBuffer, string str) {
	int lineNumber = 0;
	vector<string> myLines;
	for(int i = str.find('\n'); i != string::npos; i = str.find('\n')) {
		myLines.push_back(str.substr(0, i));
		str.erase(0, i + 1);
	}
	myLines.push_back(str);
	for(unsigned int i = 0; i < myLines.size(); i++) {
		glRasterPos2i(x, y - fontSize * lineNumber - lineBuffer * (lineNumber - 1));
		for(unsigned int j = 0; j < myLines[i].length(); j++)
			glutBitmapCharacter(font, myLines[i][j]);
		lineNumber++;
	}
}

void Idle() {
	if(!pause)
		tick(sun);
	
	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_UP:
		camPanVertical += modifier;
		break;
	case GLUT_KEY_LEFT:
		camPanHorizontal -= modifier;
		break;
	case GLUT_KEY_DOWN:
		camPanVertical -= modifier;
		break;
	case GLUT_KEY_RIGHT:
		camPanHorizontal += modifier;
		break;
	case GLUT_KEY_PAGE_UP:
		camZoom += modifier;
		break;
	case GLUT_KEY_PAGE_DOWN:
		camZoom -= modifier;
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
	case '0':
		followObject = "sun";
		break;
	case '1':
		followObject = "mercury";
		break;
	case '2':
		followObject = "venus";
		break;
	case '3':
		followObject = "earth";
		break;
	case '4':
		followObject = "mars";
		break;
	case '5':
		followObject = "jupiter";
		break;
	case '6':
		followObject = "saturn";
		break;
	case '7':
		followObject = "uranus";
		break;
	case '8':
		followObject = "neptune";
		break;
	case '+':
		modifier *= 2;
		break;
	case '-':
		modifier /= 2;
		break;
	case 'r':
		camPanHorizontal = 0;
		camPanVertical = 0;
		camZoom = 0;
		break;
	case '[':
		planetScale /= 1.1;
		break;
	case ']':
		planetScale *= 1.1;
		break;
	case '{':
		sunScale /= 1.1;
		break;
	case '}':
		sunScale *= 1.1;
		break;
	case '<':
		timeScale /= 1.1;
		break;
	case '>':
		timeScale *= 1.1;
		break;
	case '(':
		moonScale /= 1.1;
		break;
	case ')':
		moonScale *= 1.1;
		break;
	case ' ':
		pause = !pause;
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
	gluPerspective(63, double(WindowWidth) / double(WindowHeight), 0.01, 1000000);
	gluLookAt(eyex, eyey, eyez, atx, aty, atz, upx, upy, upz);

	glTranslatef(-camPanHorizontal, -camPanVertical, camZoom);
	
	glRotatef(camRotateVertical, 1, 0, 0);
	glRotatef(camRotateHorizontal, 0, 1, 0);

	if(followObject != "sun")
		glTranslatef(
			-sun.moon(followObject).distance() * orbitScale * cos(sun.moon(followObject).angularPosition() * PI / 180),
			0,
			sun.moon(followObject).distance() * orbitScale * sin(sun.moon(followObject).angularPosition() * PI / 180));
	//DRAW
	glPushMatrix();
	glColor3f(sun.red(), sun.green(), sun.blue());
	createSphere(sun.radius() * planetScale * sunScale);
	glPopMatrix();
	for(auto it = sun.begin(); it != sun.end(); ++it)
		drawPlanet(it -> second);

	// Find FPS
	static chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
	chrono::time_point<chrono::steady_clock> end;
	end = chrono::steady_clock::now();
	chrono::duration<double> elapsed = end - start;
	start = end;
	double fps = 1 / elapsed.count();

	// Text
	glViewport(0, 0, WindowWidth, WindowHeight);
	glLoadIdentity();
	gluOrtho2D(0, WindowWidth, 0, WindowHeight);
	string text =
		"FPS: " + to_string(int(fps)) +
		"\nModifier = " + to_string(modifier) +
		"\nCamPanX: " + to_string(camPanHorizontal) + 
		"\nCamPanY: " + to_string(camPanVertical) + 
		"\nFollowing: " + followObject + 
		"\nTime Speed: " + to_string(timeScale) + " days/frame" +
		"\nPlanet Size: " + to_string(planetScale * 10000) + "x";
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
		createCircle(origin.distance() * orbitScale, 1000);
	}
	glColor3f(origin.red(), origin.green(), origin.blue());
	glRotatef(origin.angularPosition(), 0, 1, 0);
	glTranslatef(origin.distance() * orbitScale, 0, 0);
	createSphere(origin.radius()*planetScale);
	for(auto it = origin.begin(); it != origin.end(); ++it) {
		glPushMatrix();
		glRotatef(it -> second.angularPosition(), 0, 1, 0);
		glTranslatef(it -> second.distance() * orbitScale * moonScale, 0, 0);
		glColor3f(it -> second.red(), it -> second.red(), it -> second.blue());
		createSphere(it -> second.radius()*planetScale);
		glPopMatrix();
	}
	glPopMatrix();
}

void tick(planet & origin) {
	origin.orbit(((1 / origin.period())) * (480.0/487.0) * timeScale);
	for(auto it = origin.begin(); it != origin.end(); ++it) {
		tick(it->second);

	}
}
