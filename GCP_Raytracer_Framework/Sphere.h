#pragma once
#include<iostream>
#include<GLM/glm.hpp>
#include<GLM/ext.hpp>
#include"Ray.h"
#include "Utils.h"
#include "RayTracingMaterial.h"

class Sphere
{
public:
	glm::vec3 Position;
	float Radius;
	struct Intersect
	{
		bool hit;
		glm::vec3 intersectPos;
		RayTracingMaterial intersectMaterial;

	};
	RayTracingMaterial material;

	Intersect RayIntersect(Ray ray);
	glm::vec3 Shade(glm::vec3 point);
	
private:

};