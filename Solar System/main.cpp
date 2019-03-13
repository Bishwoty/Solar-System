#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <map>
#include "planet.h"
using namespace std;

// Window Options
int WindowWidth = 1000;
int WindowHeight = 1000;
const char* WindowName = "Rylan Bueckert";

int WindowID;

// LookAt
double eyex = 0.0;
double eyey = 300.0;
double eyez = 0.0;
double atx = 0.0;
double aty = 0.0;
double atz = 0.0;
double upx = 1.0;
double upy = 1.0;
double upz = 0.0;

// Scaleing
double timeScale = 0.08;
double sizeScale = 0.070;
double orbitScale = 0.001;
double moonScale = 0.2;

// Objects
map<string, planet> solarSystem;

// Callback Functions
void Display();
//void Reshape(int width, int height);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Idle();
void Special(int key, int x, int y);

void init(int &argc, char ** argv);
void createPlanets();

// Shapes
void createCube();
void createPyramid();
void createSphere(float radius);



int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WindowWidth, WindowHeight);
	WindowID = glutCreateWindow(WindowName);
	glutDisplayFunc(&Display);
	glutIdleFunc(&Idle);
	//glutReshapeFunc(&Reshape);
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
	solarSystem["sun"] = planet(695.508, 0, 1);
	solarSystem["mercury"] = planet(2.4937, 57909.227, 0.2408467);
	solarSystem["venus"] = planet(6.0518, 108209.475, 0.61519726);
	solarSystem["earth"] = planet(6.371, 149598.262, 1.0000174);
	solarSystem["moon"] = planet(1.7375, 384.4, 0.074745);
	solarSystem["mars"] = planet(3.3895, 227943.824, 1.88108476);
}

void Idle() {

	for(auto it = solarSystem.begin(); it != solarSystem.end(); it++)
		it->second.orbit((1 / it->second.period()) * timeScale);

	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_UP:
		eyey += 1;
		aty += 1;
		break;
	case GLUT_KEY_LEFT:
		eyex -= 1;
		atx -= 1;
		break;
	case GLUT_KEY_DOWN:
		eyey -= 1;
		aty -= 1;
		break;
	case GLUT_KEY_RIGHT:
		eyex += 1;
		atx += 1;
		break;
	}
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'w':
		break;

	case 'a':
		break;

	case 's':
		break;

	case 'd':

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
	default:
		break;
	}
}

void createSphere(float radius) {
	glutSolidSphere(radius, 100, 100);
}

void createPyramid() {
	glBegin(GL_TRIANGLES);

	// Bottom Face
	glColor3f(0.9, 0.1, 0.1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);

	// Front Face
	glColor3f(0.1, 0.9, 0.1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0, 0.5, 0);

	// Left-Back Face
	glColor3f(0.1, 0.1, 0.9);
	glVertex3f(0, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0, 0.5, 0);

	// Right-Back Face
	glColor3f(0.9, 0.1, 0.9);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0, -0.5, -0.5);
	glVertex3f(0, 0.5, 0);

	glEnd();
}

void createCube() {
	// Create Unit Cube
	glBegin(GL_QUADS);

	// Top Face
	glColor3f(0.9, 0.1, 0.1);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	// Bottom Face
	glColor3f(0.1, 0.9, 0.1);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	// Back Face
	glColor3f(0.1, 0.1, 0.9);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	// Front Face
	glColor3f(0.9, 0.1, 0.9);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	// Left Face
	glColor3f(0.1, 0.9, 0.9);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	// Right Face
	glColor3f(0.9, 0.9, 0.1);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glEnd();
	// Cube Finished
}

void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFrustum(-10, 10, -10, 10, 20, 1000);
	gluLookAt(eyex, eyey, eyez, atx, aty, atz, upx, upy, upz);

	// Sun
	glPushMatrix();
	glColor3f(0.9, 0.1, 0.1);
	createSphere(solarSystem["sun"].radius()*sizeScale);
	glPopMatrix();

	// Mercury
	glPushMatrix();
	glRotatef(solarSystem["mercury"].angularPosition(), 0, 1, 0);
	glTranslatef(solarSystem["mercury"].distance() * orbitScale, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	createSphere(solarSystem["mercury"].radius()*sizeScale);
	glPopMatrix();
	
	// Venus
	glPushMatrix();
	glRotatef(solarSystem["venus"].angularPosition(), 0, 1, 0);
	glTranslatef(solarSystem["venus"].distance() * orbitScale, 0, 0);
	glColor3f(0.949, 0.808, 0.255);
	createSphere(solarSystem["venus"].radius()*sizeScale);
	glPopMatrix();

	// Earth
	glPushMatrix();
	glRotatef(solarSystem["earth"].angularPosition(), 0, 1, 0);
	glTranslatef(solarSystem["earth"].distance() * orbitScale, 0, 0);
	glColor3f(0.1, 0.1, 0.8);
	createSphere(solarSystem["earth"].radius()*sizeScale);
	glPopMatrix();
	
	// Moon
	glPushMatrix();
	glRotatef(solarSystem["earth"].angularPosition(), 0, 1, 0);
	glTranslatef(solarSystem["earth"].distance() * orbitScale, 0, 0);
	glRotatef(solarSystem["moon"].angularPosition(), 0, 1, 0);
	glTranslatef(solarSystem["moon"].distance() * sizeScale * moonScale, 0, 0);
	glColor3f(0.8, 0.8, 0.8);
	createSphere(solarSystem["moon"].radius()*sizeScale);
	glPopMatrix();
	
	glutSwapBuffers();
}