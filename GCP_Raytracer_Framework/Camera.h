#pragma once
#include<iostream>
#include<GLM/glm.hpp>
#include<GLM/ext.hpp>
#include<vector>
#include"Ray.h"

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

	Ray GetRay(glm::ivec2 windowPos);
	void setupCamera(glm::ivec2 windowSize);
	Ray generateRay(glm::vec4 nearPoint, glm::vec4 farPoint); // convert from screen space coords to ndc coords

	// convert screen size to -1 -> 1 z = -1 for near plane z = 1 for far plane w = 1 for both
	// create ray from near plane to far plane, coordinate on near plane give ray origin, direction from near point to far point give ray direction
	// Multiply the coordinated by the inverse projection matrix to convert to eye space
	// divide by w to convert from left handed to right handed coordinates
	// if keeping camera at 0,0,0 view matrix is just identity matrix
	// this should give two sets of coordinates in world space that can be used to define ray 
private:

};