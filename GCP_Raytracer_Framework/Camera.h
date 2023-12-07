#pragma once
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include "Ray.h"
#include <vector>

class Camera
{
	struct Viewport {
		float width,
			height,
			near,
			far,
			xOrigin,
			yOrigin;
	};
public:
	glm::mat4 proj, view, model;
	Viewport viewport;
	glm::vec3 pos = glm::vec3(0, 0, 6.0f);

	std::vector<int> wIterator;
	std::vector<int> hIterator;

	//Ray GetRay(glm::ivec2 windowPos); // Old ray generation
	void setupCamera(glm::ivec2 windowSize);
	Ray castRay(int x, int y, glm::mat4& proj, glm::mat4& view); // convert from screen space coords to ndc coords

	std::vector<glm::vec3> m_RayDirections;
	const std::vector<glm::vec3>& GetRayDirections() const { return m_RayDirections; }
	void CalculateRayDirections();
private:

};