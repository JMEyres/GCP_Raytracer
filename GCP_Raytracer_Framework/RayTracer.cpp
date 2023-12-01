#include "RayTracer.h"

glm::vec3 RayTracer::TraceRay(Ray ray)
{
	Sphere::intersect intersect;
	for (int i = 0; i < RayTracer::objectList.size(); i++)
	{
		intersect = RayTracer::objectList[i].RayIntersect(ray);
	
		if (intersect.hit)
		{
			return RayTracer::objectList[i].Shade(intersect.intersectPos);
		}
	}
	return glm::vec3(0.34f, 0.34f, 0.32f);
}

void RayTracer::CreateSphere(glm::vec3 _pos, float _radius)
{
	Sphere sphere;
	sphere.Position = _pos;;
	sphere.Radius = _radius;;

	objectList.push_back(sphere);
}