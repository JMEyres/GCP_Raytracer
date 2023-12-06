#pragma once
#include<GLM/glm.hpp>
#include <random>
#include "Sphere.h"

namespace Utils
{
	static double pi = 3.1415926535897932385;
	glm::vec3 GetNormal(glm::vec3 point, glm::vec3 spherePos);

	float RandomValue();
	glm::vec3 RandomDirection();
	glm::vec3 RandomHemisphereDirection(glm::vec3 normal);
};