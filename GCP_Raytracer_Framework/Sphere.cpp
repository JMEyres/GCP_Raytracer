#include "Sphere.h"
#include <glm/gtx/string_cast.hpp>


Sphere::Intersect Sphere::RayIntersect(Ray _ray)
{
	float d = glm::length(Position - _ray.Origin - (glm::dot((Position - _ray.Origin), _ray.Direction)) * _ray.Direction);
	float x = glm::sqrt((Radius * Radius) - (d * d));
	glm::vec3 closestIntersect = _ray.Origin + ((glm::dot((Position - _ray.Origin), _ray.Direction) - x) * _ray.Direction);

	float direction = glm::dot((Position - _ray.Origin), _ray.Direction);

	if(direction < 0)
		return Sphere::Intersect{ false, glm::vec3(0.0,0.0,0.0) };

	if(d > Radius)
		return Sphere::Intersect{ false, glm::vec3(0.0,0.0,0.0) };
	
	return Sphere::Intersect{ true, closestIntersect };
}

glm::vec3 Sphere::Shade(glm::vec3 point)
{
	glm::vec3 lightSource = glm::normalize(glm::vec3(0.0f, -1.0f, 1.0f)); // vector pointing towards the light source not the light sources position in space
	//currently every sphere will have the same shading as its hard set here rather than from a seperate light and calculated from that

	glm::vec3 colour = glm::clamp(glm::dot(lightSource, Utils::GetNormal(point, Position)), 0.0f, 1.0f) * glm::vec3(1, 1, 1) * material.colour;
	return colour;
}

