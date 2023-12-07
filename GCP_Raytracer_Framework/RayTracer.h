#pragma once
#include<iostream>
#include<GLM/glm.hpp>
#include<vector>
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Utils.h"
#include <algorithm>
#include <execution>

class GCP_Framework;
class RayTracer
{
public:
	struct HitInfo
	{
		float hitDistance;
		glm::vec3 hitPos;
		glm::vec3 hitNormal;
		int objectIndex;
	};

	std::vector<Sphere> objectList;
	std::vector<Material> materialList;

	void Render(Camera& camera, GCP_Framework& framework);
	void CreateSphere(glm::vec3 _pos, float _radius, int matIndex);
	void CreateMats();

	glm::vec4 PerPixel(int x, int y);
	
	HitInfo TraceRay(const Ray& ray);
	HitInfo ClosestHit(const Ray& ray, float hitDistance, int objectIndex);
	HitInfo Miss(const Ray& ray);
private:
	Camera* activeCamera = nullptr;
};