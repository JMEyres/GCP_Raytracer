#pragma once
#include <GLM/glm.hpp>

struct RayTracingMaterial
{
	glm::vec3 colour;
	glm::vec3 emissionColour;
	float emissionStrength;
};