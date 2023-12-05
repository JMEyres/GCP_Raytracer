#pragma once
#include<iostream>
#include<GLM/glm.hpp>
#include<vector>
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Utils.h"

class RayTracer
{
public:
	std::vector<Sphere> objectList;

	glm::vec3 TraceRay(Ray ray);
	glm::vec3 RayColor(Ray& ray, Sphere::Intersect& intersect, Sphere& sphere);

	void CreateSphere(glm::vec3 _pos, float _radius, glm::vec3 _color, float emissionStrength);
private:

};