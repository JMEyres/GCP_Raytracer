#include "Sphere.h"
#include <glm/gtx/string_cast.hpp>


Sphere::intersect Sphere::RayIntersect(Ray _ray)
{
	float d = glm::length(Position - _ray.Origin - (glm::dot((Position - _ray.Origin), _ray.Direction)) * _ray.Direction);
	float x = glm::sqrt((Radius * Radius) - (d * d));
	glm::vec3 closestIntersect = _ray.Origin + ((glm::dot((Position - _ray.Origin), _ray.Direction) - x) * _ray.Direction);

	float direction = glm::dot((Position - _ray.Origin), _ray.Direction);

	if(direction < 0)
		return Sphere::intersect{ false, glm::vec3(0.0,0.0,0.0) };

	if(d > Radius)
		return Sphere::intersect{ false, glm::vec3(0.0,0.0,0.0) };

	return Sphere::intersect{ true, closestIntersect };
}

glm::vec3 Sphere::Shade(glm::vec3 point)
{
	glm::vec3 lightSource = glm::normalize(glm::vec3(0.0f, -1.0f, 1.0f)); // vector pointing towards the light source not the light sources position in space
	//currently every sphere will have the same shading as its hard set here rather than from a seperate light and calculated from that

	glm::vec3 colour = glm::clamp(glm::dot(lightSource, GetNormal(point)), 0.0f, 1.0f) * glm::vec3(1, 1, 1) * glm::vec3(1, 0, 0);
	return colour;
}

glm::vec3 Sphere::GetNormal(glm::vec3 point)
{
	glm::vec3 center = Position;

	glm::vec3 normal = glm::normalize(point - center);// glm::vec3((point.x - center.x) / Radius, (point.y - center.y) / Radius, (point.z - center.z) / Radius);

	return normal;
}