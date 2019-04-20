#pragma once
#include <map>
#include <string>
using namespace std;

class planet {
public:
	planet();
	planet(double radius, double distance, double period, float R, float G, float B);
	double & radius();
	double & distance();
	double & period();
	double angularPosition();
	float & red();
	float & green();
	float & blue();
	map<string,planet>::iterator begin();
	map<string, planet>::iterator end();
	void orbit(double changeInAngle);
	void addMoon(string name, double radius, double distance, double period, float R, float G, float B);
	planet & moon(string name);

private:
	double planetRadius;
	double orbitalDistance;
	double orbitalPeriod;
	double orbitAngle;
	float color[3];
	map<string,planet> moons;
};