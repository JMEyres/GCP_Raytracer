#pragma once
#include <iostream>
#include <GLM/glm.hpp>
#include <vector>
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Utils.h"
#include <algorithm>
#include <execution>
#include <thread>
#include <mutex>

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

	struct Chunk
	{
		int colSize;
		int rowStart;
		int rowEnd;
	};

	std::vector<Sphere> objectList;
	std::vector<Material> materialList;

	std::vector<std::vector<glm::vec4>> passVector;

	void Render(Camera& camera, GCP_Framework& framework);
	void CreateSphere(glm::vec3 _pos, float _radius, int matIndex);
	void CreateMats();

	glm::vec4 PerPixel(int x, int y);
	
	HitInfo TraceRay(const Ray& ray);
	HitInfo ClosestHit(const Ray& ray, float hitDistance, int objectIndex);
	HitInfo Miss(const Ray& ray);

	void ParallelRayTrace(Chunk chunk);
	std::vector<Chunk> chunks;
	std::vector<std::thread> threads;
	int passes = 10;
	void CreateThreads(int numThreads, glm::ivec2 winSize);
private:
	Camera* activeCamera = nullptr;
	GCP_Framework* myFramework = nullptr;
	std::vector<glm::vec4> buffer;
};