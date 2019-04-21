#pragma once
#include <map>
#include <string>

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
	std::map<std::string,planet>::iterator begin();
	std::map<std::string, planet>::iterator end();
	void orbit(double changeInAngle);
	void addMoon(std::string name, double radius, double distance, double period, float R, float G, float B);
	planet & moon(std::string name);

private:
	double planetRadius;
	double orbitalDistance;
	double orbitalPeriod;
	double orbitAngle;
	float color[3];
	std::map<std::string,planet> moons;
};