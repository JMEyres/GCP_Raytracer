#include "Camera.h"

void Camera::setupCamera(glm::ivec2 windowSize)
{
	viewport.width = (float)windowSize.x;
	viewport.height = (float)windowSize.y;
	viewport.near = 0.1f;
	viewport.far = 1000.0f;
	
	proj = glm::perspective(glm::radians(45.0f), viewport.width/viewport.height, viewport.near, viewport.far);
	model = glm::mat4(1.0f);

}

Ray Camera::generateRay(glm::vec4 pixelPosition)
{
	Ray ray;

	// Convert coords to ndc
	pixelPosition.x = ((pixelPosition.x / viewport.width) * 2) - 1;
	pixelPosition.y = ((pixelPosition.y / viewport.height) * 2) - 1;

	// Convert coords to Eye space
	pixelPosition = pixelPosition * glm::inverse(proj);

	// Convert coords to world space
	pixelPosition = pixelPosition / 1.0f;

	// Define ray
	ray.Origin = pixelPosition;
	ray.Direction = glm::normalize(glm::vec4(0,0,-10, 0) - pixelPosition);
	//std::cout << ray.Origin.x << std::endl;
	return ray;
}

Ray Camera::GetRay(glm::ivec2 windowPos)
{
	Ray _ray;

	_ray.Origin = glm::vec3((float)windowPos.x, (float)windowPos.y, 0.0f);
	_ray.Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	return _ray;
}