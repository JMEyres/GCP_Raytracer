#pragma once
#include<iostream>
#include<GLM/glm.hpp>

struct Material
{
	glm::vec3 albedo = glm::vec3(1.0f); // surface color
	float roughness = 1.0f;
	float metalness = 0.0f;
};

class Sphere
{
public:
	glm::vec3 position;
	float radius;
	Material mat;
};