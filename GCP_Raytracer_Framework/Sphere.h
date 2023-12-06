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
	glm::vec3 colour;
	
	//glm::vec3 Shade(glm::vec3 point, Ray ray);
	
private:

};