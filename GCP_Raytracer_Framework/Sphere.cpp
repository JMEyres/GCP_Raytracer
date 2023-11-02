#include "Sphere.h"


Sphere::intersect Sphere::RayIntersect(Ray _ray)
{
	float d = glm::length(Position - _ray.Origin - (glm::dot((Position - _ray.Origin), _ray.Direction)) * _ray.Direction);
	float x = glm::sqrt((Radius * Radius) - (d * d));
	glm::vec3 closestIntersect = _ray.Origin + ((glm::dot((Position - _ray.Origin), _ray.Direction) - x) * _ray.Direction);

	glm::vec3 _delta = Position -_ray.Origin;
	float mag = glm::length(_delta);

	if (mag < (Radius))
		return Sphere::intersect{ false, glm::vec3(0.0,0.0,0.0) };

	float direction = glm::dot((Position - _ray.Origin), _ray.Direction);

	if(direction < 0)
		return Sphere::intersect{ false, glm::vec3(0.0,0.0,0.0) };

	if(d > Radius)
		return Sphere::intersect{ false, glm::vec3(0.0,0.0,0.0) };

	return Sphere::intersect{ true, closestIntersect };
}

glm::vec3 Sphere::Shade(glm::vec3 point)
{
	return glm::vec3(1.0, 0.0, 0.0);
}