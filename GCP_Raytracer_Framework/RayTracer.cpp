#include "RayTracer.h"

glm::vec3 RayTracer::TraceRay(Ray ray)
{
	Sphere::intersect intersect;
	for (int i = 0; i < RayTracer::objectList.size(); i++)
	{
		//std::cout << RayTracer::objectList[i]->Radius;
		intersect = RayTracer::objectList[i]->RayIntersect(ray);
	
		if (intersect.hit)
		{
			return glm::vec3(1, 0, 0);
		}
	}
	return glm::vec3(0);
}

void RayTracer::CreateSphere()
{
	Sphere *sphere = new Sphere();
	sphere->Position = glm::vec3(320.0, 240.0, 200.0);
	sphere->Radius = 150.0;

	objectList.push_back(sphere);
}