#include "RayTracer.h"

glm::vec3 RayTracer::TraceRay(Ray ray)
{
	Sphere::intersect intersect;
	for (int i = 0; i < RayTracer::objectList.size(); i++)
	{
		//std::cout << RayTracer::objectList[i].Position.x << std::endl;
		intersect = RayTracer::objectList[i].RayIntersect(ray);
	
		if (intersect.hit)
		{
			return RayTracer::objectList[i].Shade(intersect.intersectPos);
		}
	}
	return glm::vec3(0.34f, 0.34f, 0.32f);
}

void RayTracer::CreateSphere(glm::vec3 _pos, float _radius, Camera _camera)
{
	Sphere sphere;
	sphere.Position = _pos;;
	sphere.Radius = _radius;;

	//sphere = sphere.convertSphereToNDC(sphere, _camera.view, _camera.proj, _camera.viewport.width, _camera.viewport.height);

	objectList.push_back(sphere);
}