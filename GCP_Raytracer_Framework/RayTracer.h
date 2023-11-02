#pragma once
#include<iostream>
#include<GLM/glm.hpp>
#include<vector>
#include "Sphere.h"
#include "Ray.h"

class RayTracer
{
public:
	std::vector<Sphere*> objectList;

	glm::vec3 TraceRay(Ray ray);

	void CreateSphere();
private:

};