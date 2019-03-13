#include "planet.h"
#include <iostream>
using namespace std;

planet::planet() {
	planetRadius = 1;
	orbitalDistance = 0;
	orbitalPeriod = 1;
	orbitAngle = 0;
}

planet::planet(double radius, double distance, double period) {
	planetRadius = radius;
	orbitalDistance = distance;
	orbitalPeriod = period;
	orbitAngle = 0;
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

void planet::orbit(double changeInAngle) {
	orbitAngle += changeInAngle;
	while(orbitAngle >= 360)
		orbitAngle -= 360;
	while(orbitAngle < 0) {
		orbitAngle += 360;
	}
}
