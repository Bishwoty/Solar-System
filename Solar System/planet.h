#pragma once

using namespace std;

class planet {
public:
	planet();
	planet(double radius, double distance, double period);
	double & radius();
	double & distance();
	double & period();
	double angularPosition();
	void orbit(double changeInAngle);

private:
	double planetRadius;
	double orbitalDistance;
	double orbitalPeriod;
	double orbitAngle;
};