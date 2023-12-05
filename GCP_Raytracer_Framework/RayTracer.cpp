#include "RayTracer.h"

glm::vec3 RayTracer::TraceRay(Ray ray)
{
	Sphere::Intersect intersect;
	for (int i = 0; i < RayTracer::objectList.size(); i++)
	{
		intersect = RayTracer::objectList[i].RayIntersect(ray);
	
		if (intersect.hit)
		{
			intersect.intersectMaterial = RayTracer::objectList[i].material;
			return RayTracer::RayColor(ray, intersect, RayTracer::objectList[i]);
			//return RayTracer::objectList[i].Shade(intersect.intersectPos);
		}
	}
	return glm::vec3(0);
}

void RayTracer::CreateSphere(glm::vec3 _pos, float _radius, glm::vec3 _color, float _emissionStrength)
{
	Sphere sphere;
	sphere.Position = _pos;;
	sphere.Radius = _radius;
	sphere.material.colour = _color;
	sphere.material.emissionStrength = _emissionStrength;
	sphere.material.emissionColour = glm::vec3(1);

	objectList.push_back(sphere);
}

glm::vec3 RayTracer::RayColor(Ray& ray, Sphere::Intersect& intersect, Sphere& sphere)
{
	glm::vec3 incomingLight = glm::vec3(0);
	glm::vec3 rayColor = glm::vec3(1);
	for (int i = 0; i < 1; i++)
	{
		if (intersect.hit)
		{
			glm::vec3 normal = Utils::GetNormal(intersect.intersectPos, sphere.Position);
			glm::vec3 direction = Utils::RandomHemisphereDirection(normal,
				(ray.Origin.y * (640 * 480) + ray.Origin.x));
			std::cout << direction.x << " " << direction.y << direction.z << std::endl;
			ray.Origin = intersect.intersectPos;
			ray.Direction = direction;

			RayTracingMaterial material = intersect.intersectMaterial;
			glm::vec3 emittedLight = material.emissionColour * material.emissionStrength;
			incomingLight += emittedLight * rayColor;
			rayColor *= material.colour;
		}
		else
		{
			break;
		}
	}

	return incomingLight;
}