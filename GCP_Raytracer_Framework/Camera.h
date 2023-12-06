#pragma once
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include <vector>
#include "Ray.h"

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
	float aspectRatio;
	Viewport viewport;
	glm::vec4 raycoords;

	float cameraAngleX, cameraAngleY = 0.0f;

	//Ray GetRay(glm::ivec2 windowPos); // Old ray generation
	void setupCamera(glm::ivec2 windowSize);
	Ray castRay(int x, int y, glm::mat4& proj, glm::mat4& view); // convert from screen space coords to ndc coords
private:

};