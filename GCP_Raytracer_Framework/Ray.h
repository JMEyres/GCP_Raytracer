#pragma once
#include <iostream>
#include <GLM/glm.hpp>

class Ray
{
public:
	glm::vec4 nearPoint, farPoint; // set these in screen coords then convert to ndc
	glm::vec4 ndcNearPoint, ndcFarPoint;

	glm::vec3 Origin;
	glm::vec3 Direction;

private:

};
