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

	std::vector<int> wIterator;
	std::vector<int> hIterator;

	//Ray GetRay(glm::ivec2 windowPos); // Old ray generation
	void setupCamera(glm::ivec2 windowSize);
	Ray castRay(int x, int y, glm::mat4& proj, glm::mat4& view); // cast ray into scene from cam
	glm::vec3 const convertToNDC(glm::vec3 const coords, glm::mat4 const view, glm::mat4 const proj, glm::vec4 const viewport);
private:

};