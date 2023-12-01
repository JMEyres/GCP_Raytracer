#pragma once
#include<iostream>
#include<GLM/glm.hpp>
#include<GLM/ext.hpp>
#include"Ray.h"

class Sphere
{
public:
	glm::vec3 Position;
	float Radius;
	struct intersect
	{
		bool hit;
		glm::vec3 intersectPos;
	};

	intersect RayIntersect(Ray ray);
	glm::vec3 Shade(glm::vec3 point);
	glm::vec3 GetNormal(glm::vec3 point);
private:

};