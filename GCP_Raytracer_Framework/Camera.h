#pragma once
#include <iostream>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
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
	Viewport viewport;

	glm::vec3 cameraPos;
	float cameraAngleX, cameraAngleY;

	//Ray GetRay(glm::ivec2 windowPos); // Old ray generation
	void setupCamera(glm::ivec2 windowSize);
	void updateCameraView();
	void reCastRays();
	Ray castRay(int x, int y, glm::mat4& proj, glm::mat4& view); // convert from screen space coords to ndc coords
private:

};