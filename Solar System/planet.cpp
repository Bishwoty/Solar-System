#include "planet.h"
#include <string>

planet::planet() {
	planetRadius = 1;
	orbitalDistance = 0;
	orbitalPeriod = 1;
	orbitAngle = 0;
}

planet::planet(double radius, double distance, double period, float R, float G, float B) {
	planetRadius = radius;
	orbitalDistance = distance;
	orbitalPeriod = period;
	color[0] = R;
	color[1] = G;
	color[2] = B;
	orbitAngle = double(rand() % 36000) / 100;
}

double & planet::radius() {
	return planetRadius;
}

double & planet::distance() {
	return orbitalDistance;
}

double & planet::period() {
	return orbitalPeriod;
}

double planet::angularPosition() {
	return orbitAngle;
}

float & planet::red() {
	return color[0];
}

float & planet::green() {
	return color[1];
}

float & planet::blue() {
	return color[2];
}

std::map<std::string, planet>::iterator planet::begin() {
	return moons.begin();
}

std::map<std::string, planet>::iterator planet::end() {
	return moons.end();
}

void planet::orbit(double changeInAngle) {
	orbitAngle += changeInAngle;
	while(orbitAngle >= 360)
		orbitAngle -= 360;
	while(orbitAngle < 0) {
		orbitAngle += 360;
	}
}

void planet::addMoon(std::string name, double radius, double distance, double period, float R, float G, float B) {
	moons[name] = planet(radius, distance, period, R, G, B);
}

planet & planet::moon(std::string name) {
	return moons[name];
}

