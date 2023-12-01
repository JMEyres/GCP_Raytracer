#include "Camera.h"

void Camera::setupCamera(glm::ivec2 windowSize)
{
	viewport.width = (float)windowSize.x;
	viewport.height = (float)windowSize.y;
	viewport.near = 0.1f;
	viewport.far = 100.0f;
	
	proj = glm::perspective(glm::radians(45.0f), viewport.width/viewport.height, viewport.near, viewport.far);
	model = glm::mat4(1.0f);

}

Ray Camera::generateRay(glm::vec4 nearPoint, glm::vec4 farPoint)
{
	Ray ray;

	// Convert coords to ndc
	nearPoint.x = ((nearPoint.x / viewport.width) * 2) - 1;
	nearPoint.y = ((nearPoint.y / viewport.height) * 2) - 1;
	farPoint.x = ((farPoint.x / viewport.width) * 2) - 1;
	farPoint.y = ((farPoint.y / viewport.height) * 2) - 1;

	// Convert coords to Eye space
	nearPoint = nearPoint * glm::inverse(proj);
	farPoint = farPoint * glm::inverse(proj);

	// Convert coords to world space
	nearPoint = nearPoint / nearPoint.w;
	farPoint = farPoint / farPoint.w;

	// Define ray
	ray.Origin = nearPoint;
	ray.nearPoint = nearPoint;
	ray.farPoint = farPoint;
	ray.Direction = glm::normalize(farPoint - nearPoint);

	return ray;
}

Ray Camera::GetRay(glm::ivec2 windowPos)
{
	Ray _ray;

	_ray.Origin = glm::vec3((float)windowPos.x, (float)windowPos.y, 0.0f);
	_ray.Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	return _ray;
}