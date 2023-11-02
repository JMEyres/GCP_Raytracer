#include "Camera.h"

Ray Camera::GetRay(glm::ivec2 windowPos)
{
	Ray _ray;

	_ray.Origin = glm::vec3((float)windowPos.x, (float)windowPos.y, 0.0f);
	_ray.Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	return _ray;
}