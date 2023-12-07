#pragma once
#include<GLM/glm.hpp>

namespace Utils
{
	static double pi = 3.1415926535897932385;
	glm::vec3 GetNormal(glm::vec3 point, glm::vec3 spherePos);

	glm::vec3 RandomVector();
};