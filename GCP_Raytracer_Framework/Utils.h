#pragma once
#include<GLM/glm.hpp>
#include <random>
#include "Sphere.h"

namespace Utils
{
	static double pi = 3.1415926535897932385;

	inline double RandomDouble(); // returns random real in [0,1]
	inline double RandomDouble(double min, double max); // returns a random real in [min,max]

	inline double DegToRad(double degrees); // converts degrees to radians

	static double LengthSquared(glm::vec3 vector); // squares the length of vector
	glm::vec3 GetNormal(glm::vec3 point, glm::vec3 spherePos);

	glm::vec3 RandomVector(); // generates a random vector
	glm::vec3 RandomVector(double min, double max); // generates a random vector between min/max

	glm::vec3 UnitVector(glm::vec3 vector); // returns vector with magnitude of 1
	glm::vec3 RandomUnitVector();

	glm::vec3 RandomInUnitSphere();
	glm::vec3 RandomOnHemisphere(glm::vec3& normal);
};